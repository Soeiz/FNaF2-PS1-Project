#include <sys/types.h>
#include <stdio.h>

#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>
#include <libsnd.h>
#include <libspu.h>
#include <rand.h>
#include <libapi.h>
#include <string.h>

#include <libcd.h>
#include <malloc.h>
#include <stdbool.h>

#define BtoS(len) ( ( len + CD_SECTOR_SIZE - 1 ) / CD_SECTOR_SIZE ) 
// Name of file to load
static char * loadFile;
// libcd's CD file structure contains size, location and filename
CdlFILE filePos = {0};
//~ struct EXEC * exeStruct;
// Define start address of allocated memory
// Let's use an array so we don't have to worry about using a memory segment that's already in use.
static unsigned char ramAddr[0x40000]; // https://discord.com/channels/642647820683444236/663664210525290507/864936962199781387
// We could also set a memory address manually, but we have to make sure this won't get in the way of other routines.
// void * ramAddr = (void *)0x80030D40; 
// Load data to this buffer
u_long * dataBuffer;              
// Those are not strictly needed, but we'll use them to see the commands results.
// They could be replaced by a 0 in the various functions they're used with.
u_char CtrlResult[8];
// Value returned by CDread() - 1 is good, 0 is bad
int CDreadOK = 0;
// Value returned by CDsync() - Returns remaining sectors to load. 0 is good.
int CDreadResult = 0;

CVECTOR fntColorBG = { 0, 0, 0 };
CVECTOR fntColor = { 255, 255, 255 };

#define FONTX   960
#define FONTY   0

#define TRUECOL 1               // 0 : 16bpp, 1: 24bpp

#define VMODE 0                 // Video Mode : 0 : NTSC, 1: PAL
#define SCREENXRES 320          // Screen width
#define SCREENYRES 240          // Screen height
#define CENTERX SCREENXRES/2    // Center of screen on x 
#define CENTERY SCREENYRES/2    // Center of screen on y

#define MARGINX 0                // margins for text display
#define MARGINY 40

#define FONTSIZE 25 * 7           // Text Field Height
DISPENV disp[2];                 // Double buffered DISPENV and DRAWENV
DRAWENV draw[2];
short db = 0;                      // index of which buffer is used, values 0, 1

// Number of VAG files to load
#define VAG_NBR 19
#define MALLOC_MAX VAG_NBR            // Max number of time we can call SpuMalloc

// convert Little endian to Big endian
#define SWAP_ENDIAN32(x) (((x)>>24) | (((x)>>8) & 0xFF00) | (((x)<<8) & 0x00FF0000) | ((x)<<24))
// Memory management table ; allow MALLOC_MAX calls to SpuMalloc() - libref47.pdf p.1044

char spu_malloc_rec[SPU_MALLOC_RECSIZ * (MALLOC_MAX + 1)]; 

// Custom struct to handle VAG files
typedef struct VAGsound {
    u_char * VAGfile;        // Pointer to VAG data address
    u_long spu_channel;      // SPU voice to playback to
    u_long spu_address;      // SPU address for memory freeing spu mem
} VAGsound;

// VAG header struct (see fileformat47.pdf, p.209)
typedef struct VAGhdr {                // All the values in this header must be big endian
        char id[4];                    // VAGp         4 bytes -> 1 char * 4
        unsigned int version;          // 4 bytes
        unsigned int reserved;         // 4 bytes
        unsigned int dataSize;         // (in bytes) 4 bytes
        unsigned int samplingFrequency;// 4 bytes
        char  reserved2[12];           // 12 bytes -> 1 char * 12
        char  name[16];                // 16 bytes -> 1 char * 16
        // Waveform data after that
} VAGhdr;

// SPU settings
SpuCommonAttr commonAttributes;          // structure for changing common voice attributes
SpuVoiceAttr  voiceAttributes ;          // structure for changing individual voice attributes   

extern void display(void);

int RAN;
int Ran(int max)
{
    RAN = (rand()%max);
    if (RAN == 0) {RAN++;}
    return 0;
}

void clearVRAMMenu(void)
{
    RECT rectTL;
    setRECT(&rectTL, 700, 0, 260, 513); 
    ClearImage2(&rectTL, 0, 0, 0);
    setRECT(&rectTL, 512, 0, 128, 256); 
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

void clearVRAMloading(void)
{
    RECT rectTL;
    setRECT(&rectTL, 832, 256, 64, 128); 
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

void clearVRAMScreamer(void)
{
    RECT rectTL;
    setRECT(&rectTL, 576, 256, 106, 175); 
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

void clearVRAM(void)
{
    RECT rectTL;
    setRECT(&rectTL, 0, 0, 960, 256); //Clear all but the font
    ClearImage2(&rectTL, 0, 0, 0);
    setRECT(&rectTL, 0, 256, 1048, 256);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

void clearVRAMhallway(void)
{
    RECT rectTL;
    setRECT(&rectTL, 320, 0, 64, 0);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

int initstuff = 0;

int pad = 0;    

int frames = 500;

int menuscreeninit = 0;
int menu = 0;
int helpwantedposter = 0;

int maincustomnightmenu = 0;
int AISetmenu = 0;
int timermenu = 0;
int advancedmenu = 0;
int extramenu = 0;
int infoscreen = 0;
int unlockssubmenu = 0;

int currentmenu[2] = {0,0};

//First index, 1 Is main menu, 2 is extra menu, 3 is custom night menu.
/*
    second index (submenu) :

    submenu in extra menu :

    1 : unlocks menu
    2 : Info screen

    submenu in custom night menu :

    1 : AI set menu
    2 : timer menu
    3 : Advanced menu
*/

int freddyfacechanged = 0;
int freddyfacechangedchances = 400;

int freddylocationframelock = 300;
int bonnielocationframelock = 300;
int chicalocationframelock = 300;
int foxylocationframelock = 300;

int toyfreddylocationframelock = 300;
int toybonnielocationframelock = 300;
int toychicalocationframelock = 300;
int manglelocationframelock = 300;

int BBlocationframelock = 300;
int GFlocationframelock = 300;
//Everyone at 5 seconds !!!

int presetselector = 1;
int presetselectorlimiterright = 0;
int presetselectorlimiterleft = 0;
char presetselectorstr[20];
int animatronicategorie = 1;

int menuselection = 2;
int menuselectionmax = 4;
int musicframes = 4431;
int limitermenuL = 0;
int limitermenuR = 0;
int toyslightframe = 0;
int ranmenu = 128;
int activatedmenudebug = 0;
int printnumber = 1;
int FrameCounterlimiterup = 0;
int FrameCounterlimiterdown = 0;
int FrameCounterlimit = 0;
int convertion = 60;
int seedrandom = 0;
int unlimitedpower = 0;
char unlimitedpowerstr[] = "OFF";
char radarstr[] = "OFF";
char fastnightsstr[] = "OFF";
int radar = 0;
int limiterunlimitedpower = 0;
int limiterfastnights = 0;
int limiterradar = 0;
int fastnights = 0;
int cheating = 0;

int twoplayermode = 0;
char twoplayermodestr[] = "OFF";
int twoplayermodelimiter = 0;

int loadingframe = 0;
int goldenfreddied = 0;
int goldenfreddiedframes = 0;
int Glitch = 0;

int limiterpadright = 0;
int limiterpadleft = 0;
int limiterpaddown = 0;
int limiterpadup = 0;
int limiterbuttondown = 0;
int limiterstart = 0;
bool blockallcommands = false;
int blockcommandtimer = 0;

int freddylocation = 0;
int freddylocationframe = 300;
int freddycountdownactivation = 0;
int freddycountdown = -1;
int freddydifficulty = 0;

int toyfreddylocation = 0;
int toyfreddylocationframe = 300;
int toyfreddycountdownactivation = 0;
int toyfreddycountdown = -1;
int toyfreddydifficulty = 0;

int bonnielocation = 2;
int bonnielocationframe = 300;
int bonniedifficulty = 0;

int toybonnielocation = 0;
int toybonnielocationframe = 300;
int toybonnieframevent = 30;
int toybran = 0;
int toybonniewait = 0;
int toybonniedifficulty = 0;

int chicalocation = 0;
int chicalocationframe = 300;
int chicadifficulty = 0;

int toychicalocation = 0;
int toychicalocationframe = 300;
int toychicadifficulty = 0; 
int toychicafoolness = 0;

int foxyreadyattack = 0;
int foxylocation = 1;
int foxylocationframe = 300;
int foxydifficulty = 0;
int foxyalterablevalue = 0;
int secondframefoxy = 60;
int secondframefoxymask = 60;
int halfsecondframefoxy = 30;
int flashlightcounter = 0;
int foxysran = 0;
int foxyattackcounter = 0;
int foxystun = 0;

int manglelocation = 0;
int manglelocationframe = 300;
int manglefoolness = 240;
int mangledifficulty = 0;
int mangleattack = 0;

int BBdifficulty = 0;
int BBlocation = 0;
int BBlocationframe = 300;
int BBfoolness = 0;
int BBlol = 0;
int BBlolonce = 0;

int GFdifficulty = 0;
int GFlocationframehallway = 60;
int GFlocationframe = 300;
int GFactivated = 0;
int GFnotactivatedyet = 0;
int GFdeactivating = 0;
int GFactivatedhallway = 0;
int GFscreamerhallway = 0;
int flashedonce = 0;

int onesecondvar = 60; //always one second for some random things (vents)

int nolongerincam = 0;

int puppetdifficulty = 0;
int puppetlocation = 0;
int puppetlocationframe = 60;
int musicangerframe = 0;

int musicboxunwidingvalue = 2;
int musicboxunwidingvaludemi = 0;
int musicboxunwidingvaluthird = -2;
int musicboxtimer = 2000;
int ismusicboxatzero = 0;
int dangerlevel = 0;

int windingframessound = 0; //30
int windingframe = 1;
int toychicaHere = 0;
int toybonnieHere = 0;
int mangleHere = 0;
int BBHere = 0;

int triggeralarm = 0;

int side = 0; //0 is left, 1 is right
int jamlight = 0;
int jamlightframes = 0;
int cantlight = 0;
int cantlightR = 0;
int cantlightL = 0;

int ismaskon = 0;
int masklimiter = 0;
int maskcooldown = 30;

int light1 = 0;
int light2 = 0;
int lighthall = 0;
int issomeonehall = 0;
int lightframe = 0;

int camlimiter = 0;
int limiter2 = 0;
int limiterhall = 0;
int limiter3 = 0;
int limiterbop = 0;

int camera = 0;
int cooldowncamera = 0;
char curcam[2] = "09";
char curcamname[16] = "Show Stage";
int limitercameraD = 0;
int limitercameraU = 0;
int limitercameraR = 0;
int limitercameraL = 0;
int animatronicscamera[] = {0,0,0,0,0,0,0,0,0}; //freddy, bonnie, chica, foxy, toy freddy, toy bonnie, toy chica, mangle, BB

int flashlightbattery = 3000;
int flashlightbatteryfixed = 3000;
int batterypublic = 3;

int officequeue[5] = {0,0,0,0,0}; // only 5 members can attack on front of you. WARNING 0 is 1, 1 is 2 etc (for animatronics)
int officequeuetimer = 0;
int occupiedoncam = 360;

int animatronicsoffice[] = {0,0,0,0,0,0,0,0,0}; //freddy, bonnie, chica, foxy, toy freddy, toy bonnie, toy chica, mangle, BB
int animatronicshallway[] = {0,0,0,0,0,0,0}; //Freddy, bonnie, foxy, toy freddy, toy chica, mangle, GF

int blinkicon = 0;

int checkframes = 0;
int checklifelimit = 0;

int weirdnight = 0;
int fadeoffice = 128;
int fadeGF = 128;
int inorout = 0;
int onetime = 0;
int oldnight = 0;

int isingame = 0;
int returnedingame = 0;
int notoys = 0;
int returnframes = 0;
int returnbasevolume = 0x1800;

int noisefootstep = 0;
int framenoisefootstep = 0;
int noisefootstepanimatronic = 0;

int fivesecondframe = 300;
int ambiancesound = 1;
int ambiancechance = 1;

int mascottune = 0;
int musicmascottune = 1248;

int enablephoneguy = 1;
char enablephoneguystr[] = "ON";
int limiterphoneguy = 0;
int phoneguytalking = 0;
int phoneguytalkingconst;
int mutedcall = 0;

int isalreadydead = 0;
int isalreadydeadlow = 0;
int framedeadpossi = 60;
int lastsecondsframes = 1800;
int screamersetsound = 0;
int screamerframes = 47;
int deadtoybonnie = 0;
int dead = 0;
int deadfrom = 0;
int GFscaling = 1024;
int spriteframes = 4;
int spriteframesconst = 4;
int spritesheet = 0;

int nightwon = 0;
int fivetosixamframes = 0;
int nextnightframes = 0;
int staticframessheet = 0;

int speedoffice = 3;
int fanframes = 0;

int staticframes = 300;

int ventbanging = 0;
int ventbangingframes = 0;

int customnightactivated = 0;

int debugging = 0; //mostly for testing out animatronics on hallway and vents (with debugging their loc will not reset)

int doescharlevelup = 0;
char doescharlevelupstr[3] = "Off";

#define OTLEN 8                    // Ordering Table Length 

u_long ot[2][OTLEN];               // double ordering table of length 8 * 32 = 256 bits / 32 bytes

char primbuff[2][32768];     // double primitive buffer of length 32768 * 8 =  262.144 bits / 32,768 Kbytes

char *nextpri = primbuff[0];       // pointer to the next primitive in primbuff. Initially, points to the first bit of primbuff[0]

#define COUNT_OF(x) (sizeof(x) / sizeof(0[x]))
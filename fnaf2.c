/*
    NOOOOO RAM ISSUESSSS
    TO FIX :   
        Look at screamers*

        Not important : 

        fan animation a bit weird

        (Really) not important :

        Music box's winding down speed is a little bit incorrect on night 4 & 5 (only ~0.5/1 sec of diff)
        office left need to be fixed (can not really be seen ?)
        Finishing to fix the positions of the vents (hard asf and pos already almost fixed)

    TO MAKE (doing ideas/partially implemented things) :  
        Toy freddy hallway (test on diff night)
      Test the game on different hardware than PC and SCPH-9002 PS1

    TO DO (only ideas) :
        Implement easter eggs animatronics ? 
    TO FIX ON THE PS1 :

    FIXED ? (it is not doing that anymore but I'm not sure if it's fixed) : 

    FIXED (listed here for help if it happens again) :
      Animatronic's Icon camera going nutz : Try to place ALL of the sprites BEFORE them.
      toy chik hallway or animatronics on vents are breaking the right office's sprite : DON'T SPAM "LoadTexture"

    OTHER (info) :
      FNAF2 is a (heavily) modified version of FNAF1
      V.1.0

      *last
*/

#include "objects/constant.h"
#include "objects/objects.h"
#include "objects/camera.h"

int FrameCounter = 0;
int customAM = 12;

int AM = 12;

int night = 1;

int debug = 3; //1 is for debug without cam, 2 is animatronic debug old, 3 is only little things -- vanilla, 4 is debug for toys, 5 is for office array

//Made all of the var declarations that I won't change alot into constant.h

// extern VAG files
extern u_char _binary_vag_light_vag_start;
extern u_char _binary_vag_monitor_down_vag_start;
extern u_char _binary_vag_officesound_vag_start;
extern u_char _binary_vag_click_vag_start;
extern u_char _binary_vag_screamer_vag_start;
extern u_char _binary_vag_honk_vag_start;
extern u_char _binary_vag_jamlight_vag_start;
extern u_char _binary_vag_monitor_up_vag_start;
extern u_char _binary_vag_mask_up_vag_start;
extern u_char _binary_vag_mask_down_vag_start;
extern u_char _binary_vag_coin_vag_start;
extern u_char _binary_vag_vent1_vag_start;
extern u_char _binary_vag_vent2_vag_start;
extern u_char _binary_vag_alarm_vag_start;
extern u_char _binary_vag_windup_vag_start;
extern u_char _binary_vag_BB1_vag_start;
extern u_char _binary_vag_BB2_vag_start;
extern u_char _binary_vag_BB3_vag_start;
extern u_char _binary_vag_clickfail_vag_start;

// soundBank
VAGsound vagsoundBank[VAG_NBR] = {
      { &_binary_vag_light_vag_start,
        SPU_00CH, 0 },   
      { &_binary_vag_monitor_down_vag_start,
        SPU_01CH, 0 },
      { &_binary_vag_officesound_vag_start,
        SPU_02CH, 0 },
      { &_binary_vag_click_vag_start,
        SPU_03CH, 0 },
      { &_binary_vag_screamer_vag_start,
        SPU_04CH, 0 },
      { &_binary_vag_honk_vag_start,
        SPU_05CH, 0 },
      { &_binary_vag_jamlight_vag_start,
        SPU_06CH, 0 },
      { &_binary_vag_monitor_up_vag_start,
        SPU_07CH, 0 },
      { &_binary_vag_mask_up_vag_start,
        SPU_08CH, 0 },
      { &_binary_vag_mask_down_vag_start,
        SPU_09CH, 0 },
      { &_binary_vag_coin_vag_start,
        SPU_10CH, 0 },
      { &_binary_vag_vent1_vag_start,
        SPU_11CH, 0 },
      { &_binary_vag_vent2_vag_start,
        SPU_12CH, 0 },
      { &_binary_vag_alarm_vag_start,
        SPU_13CH, 0 },
      { &_binary_vag_windup_vag_start,
        SPU_14CH, 0 },
      { &_binary_vag_BB1_vag_start,
        SPU_15CH, 0 },
      { &_binary_vag_BB2_vag_start,
        SPU_16CH, 0 },
      { &_binary_vag_BB3_vag_start,
        SPU_17CH, 0 },
      { &_binary_vag_clickfail_vag_start,
        SPU_18CH, 0 },
};

// XA
// SPU attributes
SpuCommonAttr spuSettings;
#define CD_SECTOR_SIZE 1204
// XA
// Sector offset for XA data 4: simple speed, 8: double speed
#define XA_CHANNELS 8
#define XA_CDSPEED XA_CHANNELS >> 2
// Number of XA samples ( != # of XA files )
#define XA_TRACKS 4

typedef struct XAsound {
    u_int id;
    u_int size;
    // We can find size in sector : size / 2336, start value begins at 23, end value is at start + offset ( (size / 2336)-1 * #channels )
    // subsequent start value have an 8 bytes offset (n-1.end + 8)
    u_char file, channel;
    u_int start, end;
    int cursor;
} XAsound;

typedef struct XAbank {
    u_int index;
    int offset;
    XAsound samples[];
} XAbank;

XAbank soundBank = {
        15,
        0,
        {
            // channel 5 (silence.xa = 1496)
            // id   size   file  channel start end cursor
            {   0,  3235360,   1,     5,     0,   11072,  -1 }, //Menu.xa
            {   1,  6283840,   1,     5,     12568,   34080,  -1 }, //ambiance1.xa
            // channel 6                 
            {   2,  488224,   1,     6 ,   0,   1664, -1  }, //6am.xa
            {   3,  2620992,   1,     6 ,   3160, 12128, -1  }, //ambiance2.xa
            // Channel 7
            {   4,  941408,   1,     7 ,   0, 3216, -1  }, //static.xa 
            {   5,  8187680,   1,     7 ,   4712, 32744, -1  }, //Phone Guy Night 1.xa 
            //Channel 8
            {   6,  4996704,   1,     8 ,   0, 17104, -1  }, //Phone Guy Night 2.xa 
            {   7, 3721248,   1,     8 ,   18600, 31336, -1  }, //Phone Guy Night 3.xa  
            {   8, 2768160,   1,     8 ,   32832, 42304, -1  }, //Phone Guy Night 4.xa
            {   9, 2279936,   1,     8 ,   43800, 51600, -1  }, //Phone Guy Night 5.xa 
            //Channel 9
            {   10, 2284608,   1,     9 ,   0, 7816, -1  }, //Music End.xa 
            {   11, 2314976,   1,     9 ,   9312, 17232, -1  }, //phone guy Night 6.xa 
            {   12, 696128,   1,     9 ,   18728, 21104, -1  }, //golden freddy screamer.xa 
            {   13, 1450656,   1,     9 ,   22600, 27560, -1  }, //puppet music.xa 
            {   14, 1546432,   1,     9 ,   29056, 34344, -1  } //checking.xa 
        }
};
// XA file to load
static char * loadXA = "\\INTER8.XA;1";
// File informations : pos, size, name
CdlFILE XAPos = {0};
// CD filter
CdlFILTER filter;
// File position in m/s/f
CdlLOC  loc;

// Prototypes
void display(void);
void initSnd(void);
u_long sendVAGtoSPU(unsigned int VAG_data_size, u_char *VAG_data);
void setVoiceAttr(unsigned int pitch, long channel, unsigned long soundAddr );
u_long setSPUtransfer(VAGsound * sound);

void resetgame(int hardreset);
void print(int number);
int Ran(int max);
void screamer(void);
void gameoverprint(void);
void printNightInfo(void);
void menuselectionfunc(void);
void debugPrint(void);
void sideFunc(int number);
void timeFunc(void);
void controllerinput(void);
void LightFunc(void);
void LightFuncHall(void);
void CameraFunc(int silent);
void gamevictory(void);
void menuPrint(void);
void animatronicFunc(int init);
void AImoving(void);
/*
void FntColor(CVECTOR fgcol, CVECTOR bgcol )
{
    // The debug font clut is at tx, ty + 128
    // tx = bg color
    // tx + 1 = fg color
    // We can override the color by drawing a rect at these coordinates
    // 
    // Define 1 pixel at 960,128 (background color) and 1 pixel at 961, 128 (foreground color)
    RECT fg = { FONTX+1, FONTY + 128, 1, 1 };
    RECT bg = { FONTX, FONTY + 128, 1, 1 };
    // Set colors
    ClearImage(&fg, fgcol.r, fgcol.g, fgcol.b);
    ClearImage(&bg, bgcol.r, bgcol.g, bgcol.b);
}
*/
void LoadTexture(u_long * tim, TIM_IMAGE * tparam){     // This part is from Lameguy64's tutorial series : lameguy64.net/svn/pstutorials/chapter1/3-textures.html login/pw: annoyingmous
        OpenTIM(tim);                                   // Open the tim binary data, feed it the address of the data in memory
        ReadTIM(tparam);                                // This read the header of the TIM data and sets the corresponding members of the TIM_IMAGE structure
        
        LoadImage(tparam->prect, tparam->paddr);        // Transfer the data from memory to VRAM at position prect.x, prect.y
        DrawSync(0);                                    // Wait for the drawing to end

        if (tparam->mode & 0x8){ // check 4th bit       // If 4th bit == 1, TIM has a CLUT
            LoadImage(tparam->crect, tparam->caddr);    // Load it to VRAM at position crect.x, crect.y
            DrawSync(0);                                // Wait for drawing to end
        }
}

void init(void)
{   
    ResetCallback();
    ResetGraph(0);

    // Initialize and setup the GTE
    
    InitGeom();
    SetGeomOffset(CENTERX,CENTERY);
    SetGeomScreen(CENTERX);

    SetDefDispEnv(&disp[0], 0, 0         , SCREENXRES, SCREENYRES);     // Set display area for both &disp[0] and &disp[1]
    SetDefDispEnv(&disp[1], 0, SCREENYRES, SCREENXRES, SCREENYRES);     // &disp[0] is on top  of &disp[1]
    SetDefDrawEnv(&draw[0], 0, SCREENYRES, SCREENXRES, SCREENYRES);     // Set draw for both &draw[0] and &draw[1]
    SetDefDrawEnv(&draw[1], 0, 0         , SCREENXRES, SCREENYRES);     // &draw[0] is below &draw[1]
    // Set video mode
    if (VMODE){ SetVideoMode(MODE_PAL);}
    SetDispMask(1);                 // Display on screen    
    setRGB0(&draw[0], 0, 0, 0); // set color for first draw area
    setRGB0(&draw[1], 0, 0, 0); // set color for second draw area
    draw[0].isbg = 1;               // set mask for draw areas. 1 means repainting the area with the RGB color each frame 
    draw[1].isbg = 1;
    PutDispEnv(&disp[db]);          // set the disp and draw environnments
    PutDrawEnv(&draw[db]);
    //FntLoad(FONTX, FONTY);                // Load font to vram at FONTX,FONTY
    //FntOpen(100, 100, 48, 20, 0, 12 );    // FntOpen(x, y, width, height,  black_bg, max. nbr. chars)
    //FntColor(fntColor, fntColorBG);
    FntLoad(960, 0);
    FntOpen(MARGINX, SCREENYRES - MARGINY - FONTSIZE, SCREENXRES - MARGINX * 2, FONTSIZE, 0, 280 );
}

void display(void) {
    DrawSync(0);                    // Wait for all drawing to terminate
    VSync(0);                       // Wait for the next vertical blank
    PutDispEnv(&disp[db]);          // set alternate disp and draw environnments
    PutDrawEnv(&draw[db]);  
    DrawOTag(&ot[db][OTLEN - 1]);
    db = !db;                       // flip db value (0 or 1)
    nextpri = primbuff[db];
}


// Audio initialisation & functions
void initSnd(void){
    SpuInitMalloc(MALLOC_MAX, spu_malloc_rec);                      // Maximum number of blocks, mem. management table address.
    commonAttributes.mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR);  // Mask which attributes to set
    commonAttributes.mvol.left  = 0x3fff;                           // Master volume left
    commonAttributes.mvol.right = 0x3fff;                           // see libref47.pdf, p.1058
    commonAttributes.cd.volume.left = 0x6000;
    commonAttributes.cd.volume.right = 0x6000;
    // Apply settings
    SpuSetCommonAttr(&commonAttributes);                            // set attributes
    SpuSetIRQ(SPU_OFF);
    SpuSetKey(SpuOff, SPU_ALLCH);
}
void spuSetup(SpuCommonAttr * spuSettings)
{
    // Init Spu
    SpuInit();
    // Set master & CD volume to max
    spuSettings->mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR | SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDMIX);
    spuSettings->mvol.left  = 0x6000;
    spuSettings->mvol.right = 0x6000;
    spuSettings->cd.volume.left = 0x6000;
    spuSettings->cd.volume.right = 0x6000;
    // Enable CD input ON
    spuSettings->cd.mix = SPU_ON;
    // Apply settings
    SpuSetCommonAttr(spuSettings);
    // Set transfer mode 
    SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
}

void XAsetup()
{   
    u_char param[4];
    // ORing the parameters we need to set ; drive speed,  ADPCM play, Subheader filter, sector size
    // If using CdlModeSpeed(Double speed), you need to load an XA file that has 8 channels.
    // In single speed, a 4 channels XA is to be used.
    param[0] = CdlModeSpeed|CdlModeRT|CdlModeSF|CdlModeSize1;
    // Issue primitive command to CD-ROM system (Blocking-type)
    // Set the parameters above
    CdControlB(CdlSetmode, param, 0);
    // Pause at current pos
    CdControlF(CdlPause,0);
}

u_long sendVAGtoSPU(unsigned int VAG_data_size, u_char *VAG_data){
    u_long transferred;
    SpuSetTransferMode(SpuTransByDMA);                              // DMA transfer; can do other processing during transfer
    transferred = SpuWrite (VAG_data + sizeof(VAGhdr), VAG_data_size);     // transfer VAG_data_size bytes from VAG_data  address to sound buffer
    SpuIsTransferCompleted (SPU_TRANSFER_WAIT);                     // Checks whether transfer is completed and waits for completion
    return transferred;
}

void setVoiceAttr(unsigned int pitch, long channel, unsigned long soundAddr ){
    voiceAttributes.mask=                                   //~ Attributes (bit string, 1 bit per attribute)
    (
      SPU_VOICE_VOLL |
      SPU_VOICE_VOLR |
      SPU_VOICE_PITCH |
      SPU_VOICE_WDSA |
      SPU_VOICE_ADSR_AMODE |
      SPU_VOICE_ADSR_SMODE |
      SPU_VOICE_ADSR_RMODE |
      SPU_VOICE_ADSR_AR |
      SPU_VOICE_ADSR_DR |
      SPU_VOICE_ADSR_SR |
      SPU_VOICE_ADSR_RR |
      SPU_VOICE_ADSR_SL
    );
    voiceAttributes.voice        = channel;                 //~ Voice (low 24 bits are a bit string, 1 bit per voice )
    voiceAttributes.volume.left  = 0x0;                  //~ Volume 
    voiceAttributes.volume.right = 0x0;                  //~ Volume
    voiceAttributes.pitch        = pitch;                   //~ Interval (set pitch)
    voiceAttributes.addr         = soundAddr;               //~ Waveform data start address
    voiceAttributes.a_mode       = SPU_VOICE_LINEARIncN;    //~ Attack rate mode  = Linear Increase - see libref47.pdf p.1091
    voiceAttributes.s_mode       = SPU_VOICE_LINEARIncN;    //~ Sustain rate mode = Linear Increase
    voiceAttributes.r_mode       = SPU_VOICE_LINEARDecN;    //~ Release rate mode = Linear Decrease
    voiceAttributes.ar           = 0x0;                     //~ Attack rate
    voiceAttributes.dr           = 0x0;                     //~ Decay rate
    voiceAttributes.rr           = 0x0;                     //~ Release rate
    voiceAttributes.sr           = 0x0;                     //~ Sustain rate
    voiceAttributes.sl           = 0xf;                     //~ Sustain level
    SpuSetVoiceAttr(&voiceAttributes);                      // set attributes
    SpuSetVoiceVolume(0, 0x3500, 0x3500);//light
    SpuSetVoiceVolume(1, 0x2500, 0x2500);//monitor down
    SpuSetVoiceVolume(2, 0x2500, 0x2500);//officesound
    SpuSetVoiceVolume(3, 0x2000, 0x2000); //click
    SpuSetVoiceVolume(4, 0x4000, 0x4000);//Screamer
    SpuSetVoiceVolume(5, 0x2000, 0x2000);//honk freddy
    SpuSetVoiceVolume(6, 0x1800, 0x1800);//jamlight
    SpuSetVoiceVolume(7, 0x2500, 0x2500);//monitor up
    SpuSetVoiceVolume(8, 0x2500, 0x2500);//mask up
    SpuSetVoiceVolume(9, 0x2500, 0x2500);//mask down
    SpuSetVoiceVolume(10, 0x2000, 0x2000); //coin (blip)
    SpuSetVoiceVolume(11, 0x2000, 0x2000); //vent banging 1
    SpuSetVoiceVolume(12, 0x2000, 0x2000); //vent banging 2
    SpuSetVoiceVolume(13, 0x4000, 0x4000); //alarm
    SpuSetVoiceVolume(14, 0x2000, 0x2000); //wind up
    SpuSetVoiceVolume(15, 0x2000, 0x2000); //BB1
    SpuSetVoiceVolume(16, 0x2000, 0x2000); //BB2
    SpuSetVoiceVolume(17, 0x2000, 0x2000); //BBC- NO ! BB3...
    SpuSetVoiceVolume(18, 0x3500, 0x3500); //clickfail
}

u_long setSPUtransfer(VAGsound * sound){
    // Return spu_address
    u_long transferred, spu_address;
    u_int pitch;
    const VAGhdr * VAGheader = (VAGhdr *) sound->VAGfile;
    pitch = (SWAP_ENDIAN32(VAGheader->samplingFrequency) << 12) / 44100L; 
    spu_address = SpuMalloc(SWAP_ENDIAN32(VAGheader->dataSize));                // Allocate an area of dataSize bytes in the sound buffer. 
    SpuSetTransferStartAddr(spu_address);                                       // Sets a starting address in the sound buffer
    transferred = sendVAGtoSPU(SWAP_ENDIAN32(VAGheader->dataSize), sound->VAGfile);
    setVoiceAttr(pitch, sound->spu_channel, spu_address); 
    // Return 1 if ok, size transferred else.
    //~ if (transferred == SWAP_ENDIAN32(VAGheader->dataSize)){
        //~ return 1;
        //~ }
    //~ return transferred;
    return spu_address;
}

void MaskFunc(void) {
    if (masklimiter == 0) {
        if (maskcooldown == 0) {
            ismaskon++;
            if (ismaskon == 1) {
                SpuSetKey(SPU_ON, SPU_08CH);
                SpuSetKey(SPU_OFF, SPU_09CH);
                if (light1 == 1) {
                  sideFunc(0);
                  LightFunc();

                }
                if (light2 == 1) {
                  sideFunc(1);
                  LightFunc();

                }
                if (lighthall == 1) {
                  LightFuncHall();
                }
            }
            if (ismaskon >= 2) {
                ismaskon = 0;
                SpuSetKey(SPU_ON, SPU_09CH);
                SpuSetKey(SPU_OFF, SPU_08CH);
            }
            maskcooldown = 30;
        }
    }
    masklimiter = 1;
}

void starting(void) {
  resetgame(0);

  if (customnightactivated == 0) {
    freddylocationframe = 300;
    bonnielocationframe = 300;
    chicalocationframe = 300;
    foxylocationframe = 300;
    toyfreddylocationframe = 300;
    toybonnielocationframe = 300;
    toychicalocationframe = 300;
    manglelocationframe = 300;
    GFlocationframehallway = 60;
    GFlocationframe = 300;
    convertion = 60;
    customAM = 12;
    doescharlevelup = 1;
  }
  if (initstuff == 1) {
    clearVRAMMenu();
  } else {clearVRAMloading();}

  LoadTexture(_binary_tim_load_tim_start, &load);
  

  musicframes = 0;
  if (enablephoneguystr[1] == 'N') { // Й
      enablephoneguy = 1;
  } else {enablephoneguy = 0;}//I dunno why but it keep resetting it 

  if (fastnights == 1) {
      FrameCounterlimit = FrameCounterlimit / 2;
  }

  AM = customAM;
  FrameCounterlimit = convertion;
  FrameCounterlimit = FrameCounterlimit * 60; //60 seconds * 60 fps = 3600 frames, maybe it would cause issues with 30 fps ??
  SpuSetKey(SPU_ON, SPU_03CH);
  CdControlF(CdlPause,0);
  if (weirdnight == 0 && customnightactivated == 0) {
    animatronicFunc(1);
  }
}

void finishednight(void) {
  fivetosixamframes++;
  if (fivetosixamframes == 1) {
    gamevictory();
    mutedcall = 1;
  }
  makepoly(10); 
  if (fadeoffice > 0) {
    fadeoffice--;
    if (camera == 0) { 
      setRGB0(polyofficeright1, fadeoffice, fadeoffice, fadeoffice); 
      setRGB0(polyofficeright2, fadeoffice, fadeoffice, fadeoffice); 
      setRGB0(polyofficemiddle, fadeoffice, fadeoffice, fadeoffice);               
      setRGB0(polyofficeleft1, fadeoffice, fadeoffice, fadeoffice);                
      setRGB0(polyofficeleft2, fadeoffice, fadeoffice, fadeoffice);   
      if (lighthall == 1 && issomeonehall == 1) {
        setRGB0(polyhallway, fadeoffice, fadeoffice, fadeoffice);    
      }                  
      setRGB0(polytablemiddle, fadeoffice, fadeoffice, fadeoffice);
      setRGB0(polytableleft, fadeoffice, fadeoffice, fadeoffice);
      setRGB0(polytableright, fadeoffice, fadeoffice, fadeoffice);
      setRGB0(polytablemiddle2, fadeoffice, fadeoffice, fadeoffice);
      setRGB0(polytablefan, fadeoffice, fadeoffice, fadeoffice);
      setRGB0(polymanglehanging, fadeoffice, fadeoffice, fadeoffice);
      setRGB0(polyBB, fadeoffice, fadeoffice, fadeoffice);
    }
    if (camera == 1) {
      setRGB0(polylayout, fadeoffice, fadeoffice, fadeoffice);    
    }
    if (ismaskon == 1) {
      setRGB0(polymask, fadeoffice, fadeoffice, fadeoffice);
    }
    setRGB0(polyfiveam, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);    
  } else {
    setRGB0(polyfiveam, 128, 128, 128);   
    if (camera == 0) { 
      setRGB0(polyofficeright1, 0, 0, 0); 
      setRGB0(polyofficeright2, 0, 0, 0); 
      setRGB0(polyofficemiddle, 0, 0, 0);               
      setRGB0(polyofficeleft1, 0, 0, 0);                
      setRGB0(polyofficeleft2, 0, 0, 0);            
      setRGB0(polyhallway, 0, 0, 0);
      setRGB0(polytablemiddle, 0, 0, 0);
      setRGB0(polytableright, 0,0,0);
      setRGB0(polytablemiddle2, 0, 0, 0);
      setRGB0(polytablefan, 0, 0, 0);
      setRGB0(polytableleft, 0, 0, 0);
      setRGB0(polymanglehanging, 0, 0, 0);
      setRGB0(polyBB, 0, 0, 0);
    }
    if (camera == 1) {
      CameraFunc(1);
    }
    if (ismaskon == 1) {
      setRGB0(polymask, 0, 0, 0);
    }
  }
  if (fivetosixamframes == 89){
      LoadTexture(_binary_tim_5am6_5AM1_tim_start, &fiveam);
  }
  if (fivetosixamframes == 101){
      LoadTexture(_binary_tim_5am6_5AM2_tim_start, &fiveam);
  }
  if (fivetosixamframes == 113){
      LoadTexture(_binary_tim_5am6_5AM3_tim_start, &fiveam);
  }
  if (fivetosixamframes == 125){
      LoadTexture(_binary_tim_5am6_5AM4_tim_start, &fiveam);
  }
  if (fivetosixamframes == 137){
      LoadTexture(_binary_tim_5am6_5AM5_tim_start, &fiveam);
  }
  if (fivetosixamframes == 181){
      LoadTexture(_binary_tim_5am6_6AM1_tim_start, &fiveam);
  }
  if (fivetosixamframes == 193){
      LoadTexture(_binary_tim_5am6_6AM2_tim_start, &fiveam);
  }
  if (fivetosixamframes == 205){
      LoadTexture(_binary_tim_5am6_6AM3_tim_start, &fiveam);
  }
  if (fivetosixamframes == 217){
      LoadTexture(_binary_tim_5am6_6AM4_tim_start, &fiveam);
  }
  if (fivetosixamframes == 229){
      LoadTexture(_binary_tim_5am6_6AM5_tim_start, &fiveam);
  }
  if (fivetosixamframes == 241){
      LoadTexture(_binary_tim_5am6_6AM6_tim_start, &fiveam);
  }
}

void checking(void) {
  if (camera == 0) {
    if (checkframes == 0) {
      switch(officequeue[0]) {
        case 1:
          LoadTexture(_binary_tim_office_officeFREDDY_tim_start, &officefrontanimatronic);
          break;
        case 2:
          LoadTexture(_binary_tim_office_officeBONNIE_tim_start, &officefrontanimatronic);
          break;
        case 3:
          LoadTexture(_binary_tim_office_officeCHICA_tim_start, &officefrontanimatronic);
          break;
        case 5:
          LoadTexture(_binary_tim_office_officeTOYFREDDY_tim_start, &officefrontanimatronic);
          break;
        case 6:
          LoadTexture(_binary_tim_office_officeTOYBONNIE_tim_start, &officefrontanimatronic);
          break;

        if (phoneguytalking > 0) {
            mutedcall = 1;
            phoneguytalking = 0;
        }
      }
    }
      checkframes++;
      if (checkframes < 100) {
          MovVectorofficefronttoybonnie.vx = MovVectorofficefronttoybonnie.vx - 1;
      }
      if (checkframes > 100 && checkframes < 125) {
          if (checkframes %2 == 0) {
              MovVectorofficefronttoybonnie.vx = MovVectorofficefronttoybonnie.vx - 1;
          }
      }
      if (checkframes > 125) {
          if (checkframes %3 == 0) {
              MovVectorofficefronttoybonnie.vx = MovVectorofficefronttoybonnie.vx - 1;
          }
      }
      Ran(8);
      if (RAN == 1 && MovVectorofficefronttoybonnie.vy < -54) {MovVectorofficefronttoybonnie.vy++;}
      if (RAN == 2 && MovVectorofficefronttoybonnie.vy > -56) {MovVectorofficefronttoybonnie.vy--;}
      if (checkframes < 240) {
          if (checkframes %3 == 0) {         
              setRGB0(polyofficeright1, 0, 0, 0); 
              setRGB0(polyofficeright2, 0, 0, 0); 

              setRGB0(polyofficemiddle, 0, 0, 0);   

              setRGB0(polyofficefront, 0, 0, 0);            
              setRGB0(polyofficeleft1, 0, 0, 0);            
              setRGB0(polyofficeleft2, 0, 0, 0);    

              setRGB0(polyhallway, 0, 0, 0);       
              setRGB0(polytablefan, 0, 0, 0);     
              setRGB0(polytablemiddle, 0, 0, 0);    
              setRGB0(polytableright, 0,0,0);  
              setRGB0(polytableleft, 0,0,0);
              setRGB0(polytablemiddle2, 0, 0, 0);
              setRGB0(polymanglehanging, 0, 0, 0);
              setRGB0(polyBB, 0, 0, 0);
          } else {
              setRGB0(polyofficeright1, 128, 128, 128); 
              setRGB0(polyofficeright2, 128, 128, 128); 
              setRGB0(polyofficemiddle, 128, 128, 128);     
              setRGB0(polyofficefront, 128, 128, 128);               
              setRGB0(polyofficeleft1, 128, 128, 128);               
              setRGB0(polyofficeleft2, 128, 128, 128);  
              if (lighthall == 1 && issomeonehall == 1) {
                  setRGB0(polyhallway, 108, 108, 108);     
              }             
              setRGB0(polytableright, 108, 108, 108);
              setRGB0(polytableleft, 108, 108, 108);
              setRGB0(polytablemiddle, 108, 108, 108);    
              setRGB0(polytablemiddle2, 108, 108, 108);
              setRGB0(polytablefan, 108, 108, 108);    
              setRGB0(polymanglehanging, 128,128,128);
              setRGB0(polyBB, 128,128,128);
          }
      } else {
          setRGB0(polyofficeright1, 0, 0, 0); 
          setRGB0(polyofficeright2, 0, 0, 0); 
          setRGB0(polyofficemiddle, 0, 0, 0);               
          setRGB0(polyofficefront, 0, 0, 0);            
          setRGB0(polyofficeleft1, 0, 0, 0);             
          setRGB0(polyofficeleft2, 0, 0, 0);            
          setRGB0(polyhallway, 0, 0, 0);    
          setRGB0(polytablemiddle, 0, 0, 0);       
          setRGB0(polytableright, 0,0,0); 
          setRGB0(polytableleft, 0,0,0);
          setRGB0(polytablemiddle2, 0, 0, 0);
          setRGB0(polytablefan, 0, 0, 0);
          setRGB0(polymanglehanging, 0, 0, 0);    
          setRGB0(polyBB, 0, 0, 0);
      }
      if (checkframes == checklifelimit) {
        if (ismaskon == 0) {
          isalreadydead = 3; //3 is by office attack
        }
      }
      if (checkframes == 300) {
        if (ismaskon == 0) {
            isalreadydead = 4; //Office attack too but only when you lower the cam down
        }
          officequeuetimer = 600;
          checkframes = 0;
          if (ismaskon == 1 && isalreadydead != 3) {
            switch(officequeue[0]) {
              case 1:
                freddylocation = 0;
                freddylocationframe = 300;
                break;
              case 2:
                bonnielocation = 1;
                bonnielocationframe = 300;
                break;
              case 3:
                chicalocation = 1;
                chicalocationframe = 300;
                break;
              case 5:
                toyfreddylocation = 0;
                toyfreddylocationframe = 300;
                break;
              case 6:
                toybonnielocation = 1;
                toybonnielocationframe = 300;
                MovVectorofficefronttoybonnie.vx = 0;
                break;
            }
            officequeue[0] = 0;
            for (int i = 0; i < 4; i++){ officequeue[i] = officequeue[i + 1];}
            officequeue[4] = 0;
          }
          CdControlF(CdlPause,0);
          /*
          for (int i = 0; i<10;i++) {
              if(animatronicsoffice[i] == 1)
              {
                  animatronicsoffice[i] = 0;
              } // TO-DO After the loc array
          }*/ 
          fadeoffice = 0;
      }
    } else {
    occupiedoncam--;
    if (occupiedoncam == 0) {
        isalreadydead = 3;
    }
  }
}
/*
int makestring(char * test, char * var) {
  for (int i; i < 10; i++) {
    var[i] = ' ';
  }
  var = strcpy(malloc(strlen(test)+1),test);
}
*/
int main(void) {
    //controller
    TILE * PADL;                    // Tile primitives
    TILE * TRIGGERL;
    TILE * PADR;
    TILE * TRIGGERR;
    TILE * START, * SELECT;

    int sample = -1;

    init();

    //SPU
    u_long spu_address;
    spuSetup(&spuSettings);
    // Init sound settings
    initSnd();

    PadInit(0);                     // Initialize pad.  Mode is always 0

    for (u_short vag = 0; vag < VAG_NBR; vag++ ){
        vagsoundBank[vag].spu_address = setSPUtransfer(&vagsoundBank[vag]);
    }

    // Init CD system
    CdInit();

    // Init heap
    InitHeap((u_long *)ramAddr, sizeof(ramAddr));

    clearVRAM();
    //LoadTexture(_binary_tim_fnt_tim_start, &fontface);
    while (1)
    {   
        ClearOTagR(ot[db], OTLEN);
        
        pad = PadRead(0);
        // if sample is set
        if (sample != -1 ){
            // Begin XA file playback...
            // if sample's cursor is 0
            if (soundBank.samples[sample].cursor == 0){
                // Convert sector number to CD position in min/second/frame and set CdlLOC accordingly.
                CdIntToPos( soundBank.samples[sample].start + soundBank.offset , &loc);
                // Send CDROM read command
                CdControlF(CdlReadS, (u_char *)&loc);
                // Set playing flag
            }
            // if sample's cursor is close to sample's end position, stop playback
            if ((soundBank.samples[sample].cursor += XA_CDSPEED) >= soundBank.samples[sample].end - soundBank.samples[sample].start  ){
                CdControlF(CdlStop,0);
                soundBank.samples[sample].cursor = -1;
                sample = -1;
            }
        }
        if (menu == 0) { //Menu Screen
            if (helpwantedposter == 0) {

                menuPrint();
    
                menuselectionfunc();
    
                if (musicframes == 4431){
                    musicframes = 0;
                    sample = 0;
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);
                    soundBank.samples[sample].cursor = 0;
                } else {musicframes++;}
    
                if (menuscreeninit == 0) {
                loadFile = "\\MENUS1.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &menus1); 
                free(dataBuffer);
                loadFile = "\\MENUS2.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &menus2); 
                free(dataBuffer);
                if (initstuff == 0) {
                    loadFile = "\\HWANTED.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &helpwanted); 
                    free(dataBuffer);
                    loadFile = "\\GAMEOVER.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &gameover); 
                    free(dataBuffer);
                    loadFile = "\\GJFIV.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &goodjob); 
                    free(dataBuffer);
                    initstuff++;
                }
                CdControlF(CdlPause,0);
                          
                // Load XA file from cd
                // Find XA file pos
                CdSearchFile( &XAPos, loadXA);
                // Set cd head to start of file
                soundBank.offset = CdPosToInt(&XAPos.pos);
                // Set cd XA playback parameters and pause cd
                XAsetup();
                // Keep track of XA Sample currently playing

                menuscreeninit = 1;
                musicframes = 4431;
                }
                if (menuscreeninit == 1) {

                seedrandom++;
                //TIM toys
                makepoly(1);
                }
            } else {
                loadingframe++;

                if (loadingframe == 1) {
                    musicframes = 3787;
                    if (ambiancesound > 3) {ambiancesound = 1;}
                }
                if (loadingframe < 360) {

                    //Help wanted bg
                    makepoly(2);

                    if (loadingframe > 100) {
                        if (pad & PADstart) {
                            loadingframe = 360;
                        }
                    }
                }
                if (loadingframe > 240) {
                    if (fadeoffice < 128) {fadeoffice++;}

                    setRGB0(polyhelpwanted, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);   
                } else {
                    if (fadeoffice > 0) {fadeoffice--;}

                    setRGB0(polyhelpwanted, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);   
                }
                if (loadingframe > 360) {
                    menu = 1;
                    helpwantedposter = 0;
                }
            }
        }//Menu Screen
        if (menu == 1) { //Loading/Starting night screen
            loadingframe++;

            if (loadingframe < 360) {loadingframe = 360;}

            if (loadingframe == 370 && onetime == 0) {
              starting();
              srand(seedrandom); // "truly" "random"
              Ran(seedrandom * 68574 + seedrandom / 2);
              srand(RAN); //Truly random x2
              Ran(8500);
              if (RAN == 1) {
                weirdnight = 1;
                oldnight = night;
                night = 725255;
                onetime++;
              }
            }

            if (loadingframe < 560 && loadingframe > 360) {
                printNightInfo();

            } else {
                makepoly(13);
            }

            if (loadingframe == 500) {
                Ran(10000);
            }
            if (loadingframe == 560) {
                LoadTexture(_binary_tim_office_oLEFTpart2_tim_start, &officeLEFT);//Loading rest of the things
                LoadTexture(_binary_tim_office_oRIGHTpart2_tim_start, &officeRIGHT);
                LoadTexture(_binary_tim_office_officeMIDDLE_tim_start, &officeMIDDLE);
                LoadTexture(_binary_tim_hallway_toychicahallway_tim_start, &animatronichallway);
                LoadTexture(_binary_tim_office_mutecall_tim_start, &mutecall);
                LoadTexture(_binary_tim_office_officeFREDDY_tim_start, &officefrontanimatronic);
            }/* OLTchic.TIM
                OLTBB.TIM*/
            if (loadingframe == 570) {
                if (night == 6) {LoadTexture(_binary_tim_GJSIX_tim_start, &goodjob);}
                if (initstuff == 1) {
                    loadFile = "\\OLEFTP1.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &officeLEFT); 
                    free(dataBuffer);
                    loadFile = "\\TCENTER.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &tableCENTER); 
                    free(dataBuffer);
                    LoadTexture(_binary_tim_office_fan1_tim_start, &tableFAN);
                    loadFile = "\\ORIGHTP1.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &officeRIGHT); 
                    free(dataBuffer);
                    loadFile = "\\MASK.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &mask); 
                    free(dataBuffer);
                    loadFile = "\\LAYOUT.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &layout); 
                    free(dataBuffer);
                    loadFile = "\\TRIGHT.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &tableRIGHT); 
                    free(dataBuffer);
                    loadFile = "\\TLEFT.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &tableLEFT); 
                    free(dataBuffer);
                }
            } 
            if (loadingframe == 580) {
                if (initstuff == 1) {
                    loadFile = "\\BB.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &BB); 
                    free(dataBuffer);
                    loadFile = "\\GF.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &GF); 
                    free(dataBuffer);
                    loadFile = "\\OLTCHIC.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &Rvent); 
                    free(dataBuffer);
                    loadFile = "\\ORTBON.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &Lvent); 
                    free(dataBuffer);
                    loadFile = "\\ORTMAN.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &Lvent); 
                    free(dataBuffer);
                    loadFile = "\\OLTBB.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &Rvent); 
                    free(dataBuffer);
                    initstuff++;
                }
                CdSearchFile( &XAPos, loadXA);
                soundBank.offset = CdPosToInt(&XAPos.pos);
                XAsetup();  
           } 
           if (loadingframe > 630) {
                if (initstuff == 2) {
                    initstuff++;
                }
           }
            if (loadingframe > 660) {
                menu = 2;
                SpuSetKey(SPU_ON, SPU_02CH);
                loadingframe = 0;
            }
        }//Loading/Starting night screen
        if (menu == 2) { //Gameplay Screen
            timeFunc();   

            if (AM == 6 && FrameCounter == 0) {
                nightwon = 1;
                sample = 2;
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);
                soundBank.samples[sample].cursor = 0;
            }

            if (fivetosixamframes < 720 && AM == 6) {
              finishednight();
            }
            if (fivetosixamframes > 719) {
                if (night == 5 || night == 6 || night == 7) {
                    nextnightframes++;
                    if (nextnightframes == 1) {
                        sample = 10; //Sample is for the music playing, 13 normal, 18 funky
                        filter.chan = soundBank.samples[sample].channel;
                        filter.file = soundBank.samples[sample].file;
                        CdControlF(CdlSetfilter, (u_char *)&filter);

                        soundBank.samples[sample].cursor = 0;
                    }
                    makepoly(11);

                    if (pad & PADstart && night != 7 || nextnightframes == 3600 && night != 7) {
                        if (night != 6) {
                            night++;
                        }
                        fivetosixamframes = 0;
                        nextnightframes = 0;
                        menu = 1;
                    } 
                } else {
                    if (night == 725255) {
                      night = oldnight;
                    } else {night++;}
                    fivetosixamframes = 0;
                    nextnightframes = 0;
                    menu = 1; //Load into next night
                }
            }

            if (dead == 1) {
              if (screamersetsound == 0) {
                  sample = 14;
                  filter.chan = soundBank.samples[sample].channel;
                  filter.file = soundBank.samples[sample].file;
                  CdControlF(CdlSetfilter, (u_char *)&filter);
                  soundBank.samples[sample].cursor = 0;
                  screamersetsound++;
              }
              screamer();
            } else {
              if (fivetosixamframes == 0) {
                print(printnumber);
                animatronicFunc(0);
                controllerinput();
              }
            }
            if (activatedmenudebug == 1 && pad & PADR1 && pad & PADRup && pad & PADRright && pad & PADL2) {
                AM = 5;
                FrameCounter = FrameCounterlimit - 60;
            }
            if (camera == 1) { //Cam things
                cameraloc();
            }
            
            if (fivesecondframe == 0 && night != 725255) {
                if (phoneguytalking == 0 && AM != 6 && ismusicboxatzero == 0) {
                    Ran(10);
                    if (ambiancechance > RAN) {
                        if (ambiancesound == 1) {
                            sample = 1;
                            fivesecondframe = 8580;
                        }
                        if (ambiancesound == 2) {
                            sample = 3;
                            fivesecondframe = 3600;
                        }
                        ambiancesound++;
                        ambiancechance = 1;
                        filter.chan = soundBank.samples[sample].channel;
                        filter.file = soundBank.samples[sample].file;
                        CdControlF(CdlSetfilter, (u_char *)&filter);
                        soundBank.samples[sample].cursor = 0;
                    }else {
                        ambiancesound++;
                        fivesecondframe = 300;
                        ambiancechance++;
                    }   
                    if (ambiancesound > 2) {
                        ambiancesound = 1;
                    }
                }
            }

            if (fivesecondframe > 0) {fivesecondframe--;}

            if (phoneguytalkingconst - 1620 < phoneguytalking && mutedcall == 0) {
              if (pad & PADselect || pad >> 16 & PADselect) {
                mutedcall = 1;
                CdControlF(CdlPause,0);
                phoneguytalking = 0;
              }
            }
              
            if (ismusicboxatzero == 1) {
                if (musicangerframe == 0) {
                    if (phoneguytalking > 0) {
                        mutedcall = 1;
                        CdControlF(CdlPause,0);
                        phoneguytalking = 0;
                    }

                    musicangerframe = 1984;
                    sample = 13;
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);
                    soundBank.samples[sample].cursor = 0;
                } else {
                    musicangerframe--;
                }
            }

            if (noisefootstep == 1) {
                framenoisefootstep++;
                int noise;
                if (framenoisefootstep == 1) {
                    if (noisefootstepanimatronic == 1) { //Bonnie
                        noise = noise + bonnielocation * 300;
                    }
                    if (noisefootstepanimatronic == 2) { //Chica
                        noise = noise + chicalocation * 300; // chicalocation == 1 -> +300, == 7 -> +1400
                    }
                    SpuSetVoiceVolume(8, noise, noise);
                    SpuSetKey(SPU_ON, SPU_08CH);
                }
                if (framenoisefootstep == 60) {
                    SpuSetVoiceVolume(8, noise - 600, noise - 600); //For making it quieter
                    SpuSetKey(SPU_ON, SPU_08CH);
                    noisefootstep--;
                    framenoisefootstep = 0;
                    noise = 0;
                }
            }

            if (noisefootstepF == 1) {
                int noisef;
                noisef = 0x800;
                noisef = noisef + freddylocation * 1000;
                SpuSetVoiceVolume(13, noisef, noisef);
                SpuSetKey(SPU_ON, SPU_13CH);
                noisefootstepF--;
                noisef = 0;
            }
            if (jamlight == 1) {
                jamlightframes++;
                if (jamlightframes == 1) {SpuSetKey(SPU_ON, SPU_12CH);}
                if (jamlightframes == 5) {
                    SpuSetKey(SPU_ON, SPU_12CH);
                    jamlight--;
                    jamlightframes = 0;
                }
            }

            if (officequeue[0] != 0 && officequeuetimer == 0) {
              checking();
              if (checkframes == 1) {
                if (sample != 14) {
                 sample = 14;
                }
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);
                soundBank.samples[sample].cursor = 0;  
              }
              if (checkframes == 300) {sample = 0;}
            }

                if (fadeoffice != 128 && officequeuetimer != 0) {
                    fadeoffice++;
                      setRGB0(polyofficeright1, fadeoffice, fadeoffice, fadeoffice); 
                      setRGB0(polyofficeright2, fadeoffice, fadeoffice, fadeoffice); 
                      setRGB0(polyofficemiddle, fadeoffice, fadeoffice, fadeoffice);               
                      setRGB0(polyofficeleft1, fadeoffice, fadeoffice, fadeoffice);            
                      setRGB0(polyofficeleft2, fadeoffice, fadeoffice, fadeoffice);  
                      if (lighthall == 1 && issomeonehall == 1) {
                        setRGB0(polyhallway, fadeoffice, fadeoffice, fadeoffice);      
                      }             
                      setRGB0(polytablefan, fadeoffice, fadeoffice, fadeoffice);   
                      setRGB0(polytablemiddle, fadeoffice, fadeoffice, fadeoffice);   
                      setRGB0(polytableright, fadeoffice, fadeoffice, fadeoffice);   
                      setRGB0(polytableleft, fadeoffice, fadeoffice, fadeoffice);   
                      setRGB0(polytablemiddle2, fadeoffice, fadeoffice, fadeoffice);
                      setRGB0(polymanglehanging, fadeoffice, fadeoffice, fadeoffice);
                      setRGB0(polyBB, fadeoffice, fadeoffice, fadeoffice);
                } else {

                  if (night != 725255 && fivetosixamframes == 0 && checkframes == 0) {
                    setRGB0(polyofficeright1, 128, 128, 128); 
                    setRGB0(polyofficeright2, 128, 128, 128); 
                    setRGB0(polyofficemiddle, 128, 128, 128);           
                    setRGB0(polyofficefront, 128, 128, 128);                   
                    setRGB0(polyofficeleft1, 128, 128, 128);                    
                    setRGB0(polyofficeleft2, 128, 128, 128);     
                    if (lighthall == 1 && issomeonehall == 1) {
                        setRGB0(polyhallway, 108, 108, 108);     
                    }             
                    setRGB0(polytablefan, 128, 128, 128);   
                    setRGB0(polytablemiddle, 108, 108, 108);    
                    setRGB0(polytableright, 108, 108, 108);
                    setRGB0(polytableleft, 108, 108, 108);    
                    setRGB0(polytablemiddle2, 108, 108, 108);    
                    setRGB0(polymanglehanging, 128, 128, 128);
                    setRGB0(polyBB, 128, 128, 128);
                  }
                }

            if (ismaskon == 0 && isalreadydead == 3 && checkframes == 0 || camera == 0 && isalreadydead == 4 && cooldowncamera != 0) {
              dead = 1;
              deadfrom = officequeue[0];
            }
            if (camera == 0 && isalreadydead == 5 && cooldowncamera != 0) {dead = 1;}
            
            if (officequeuetimer > 1) {officequeuetimer--;}

            if (officequeuetimer == 1 && camera == 1) {officequeuetimer--;} //Like that, animatronics have to wait 

            if (ventbanging == 1) {
              ventbangingframes++;
              if (ventbangingframes == 1) {
                SpuSetKey(SPU_ON, SPU_11CH);
              }
              if (ventbangingframes == 37) {
                SpuSetKey(SPU_ON, SPU_12CH);
              }
              if (ventbangingframes == 74) {
                SpuSetKey(SPU_ON, SPU_11CH);
              }
              if (ventbangingframes == 111) {
                SpuSetKey(SPU_ON, SPU_12CH);
              }
              if (ventbangingframes == 148) {
                SpuSetKey(SPU_ON, SPU_11CH);
              }
              if (ventbangingframes == 190) {
                ventbanging = 0;
                ventbangingframes = 0;
              }
            }

            if (AM == 12 && FrameCounter == 1) { //Init Gameplay
                CdControlF(CdlPause,0);
                LoadTexture(_binary_tim_timer_timer20_tim_start, &timermusicbox); 
            }
            if (enablephoneguy == 1) {
                if (night == 1) {
                    phoneguytalking = 11172;
                    phoneguytalkingconst = 11172;
                    sample = 5;
                }
                if (night == 2) {
                    phoneguytalking = 5544;
                    phoneguytalkingconst = 5544;
                    sample = 6;
                }
                if (night == 3) {
                    phoneguytalking = 5040;
                    phoneguytalkingconst = 5040;
                    sample = 7;
                }
                if (night == 4) {
                    phoneguytalking = 3762;
                    phoneguytalkingconst = 3762;
                    sample = 8;
                }
                if (night == 5) {
                    phoneguytalking = 3036;
                    phoneguytalkingconst = 3036;
                    sample = 9;
                }
                if (night == 6) {
                    phoneguytalking = 3180;
                    phoneguytalkingconst = 3180;
                    sample = 11;
                }
                if (night == 725255) {
                    phoneguytalking = 3300;
                    phoneguytalkingconst = 3300;
                    sample = 10;
                }
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);
                soundBank.samples[sample].cursor = 0;
                enablephoneguy = 0;
            }
            if (phoneguytalking > 0) {phoneguytalking--;}
            if (phoneguytalking == 1) {
              sample = 0;
              CdControlF(CdlPause,0);
            }

            if (night == 725255) {
              if (phoneguytalking > 784 && fivetosixamframes == 0) {
                setRGB0(polyofficeright1, 128, 128, 128); 
                setRGB0(polyofficeright2, 128, 128, 128); 
                setRGB0(polyofficemiddle, 128, 128, 128);               
                setRGB0(polyofficeleft1, 128, 128, 128);               
                setRGB0(polyofficeleft2, 128, 128, 128);                
                setRGB0(polytablefan, 128, 128, 128);           
                setRGB0(polytablemiddle, 128, 128, 128);    
                setRGB0(polytableright, 128, 128, 128);    
                setRGB0(polytableleft, 128, 128, 128);    
                setRGB0(polytablemiddle2, 128, 128, 128);    
                setRGB0(polymanglehanging, 128, 128, 128);
                setRGB0(polyBB, 128, 128, 128);
              } else {
                if (phoneguytalking % 3 == 0 && fadeoffice > 0) {
                  fadeoffice--;
                  setRGB0(polyofficeright1, fadeoffice, fadeoffice, fadeoffice); 
                  setRGB0(polyofficeright2, fadeoffice, fadeoffice, fadeoffice); 
                  setRGB0(polyofficemiddle, fadeoffice, fadeoffice, fadeoffice);               
                  setRGB0(polyofficeleft1, fadeoffice, fadeoffice, fadeoffice);                
                  setRGB0(polyofficeleft2, fadeoffice, fadeoffice, fadeoffice);                   
                  setRGB0(polytablefan, fadeoffice, fadeoffice, fadeoffice);              
                  setRGB0(polytablemiddle, fadeoffice, fadeoffice, fadeoffice);             
                  setRGB0(polytablemiddle2, fadeoffice, fadeoffice, fadeoffice);             
                  setRGB0(polytableright, fadeoffice, fadeoffice, fadeoffice);  
                  setRGB0(polytableleft, fadeoffice, fadeoffice, fadeoffice);  
                  setRGB0(polyBB, fadeoffice, fadeoffice, fadeoffice);  
                  SpuSetVoiceVolume(2, 0x00, 0x00);//officesound     
                }
              }
              if (phoneguytalking == 2100) {
                if (lighthall == 1) {LightFuncHall();}
                toychicalocation = 2;
              }
              if (phoneguytalking == 1900) {
                if (lighthall == 1) {LightFuncHall();}
                toychicalocation = 0;
              }
              if (phoneguytalking == 960) {
                if (camera == 1) {
                  CameraFunc(0);
                }
                if (ismaskon == 1) {
                  MaskFunc();
                }
                if (light1 == 1) {
                  sideFunc(1);
                  LightFunc();
                }
                if (light2 == 1) {
                  sideFunc(2);
                  LightFunc();
                }
                if (lighthall == 1) {
                  LightFuncHall();
                }
              }
              if (phoneguytalking == 750) {
                toychicalocation = 0;
                AM = 5;
                FrameCounter = 1400;
              }
            }

            if (cooldowncamera > 0) {cooldowncamera--;}
            if (maskcooldown > 0) {maskcooldown--;}
            if (phoneguytalkingconst - 1620 < phoneguytalking && mutedcall == 0) {

              polymutecall = (POLY_FT4 *)nextpri;                 
                      
              RotMatrix(&RotVectormutecall, &PolyMatrixmutecall);    
              TransMatrix(&PolyMatrixmutecall, &MovVectormutecall);  
              ScaleMatrix(&PolyMatrixmutecall, &ScaleVectormutecall);
              
              SetRotMatrix(&PolyMatrixmutecall);                  
              SetTransMatrix(&PolyMatrixmutecall);                
              
              setClut(polymutecall, 960, 200);
  
                    setRGB0(polymutecall, 128, 128, 128); 

              setPolyFT4(polymutecall);                           
              
              polymutecall->tpage = getTPage(mutecall.mode&0x3, 0, 704, 256); 
              
              
              RotTransPers4(
                          &VertPosmutecall[0],      &VertPosmutecall[1],      &VertPosmutecall[2],      &VertPosmutecall[3],
                          (long*)&polymutecall->x0, (long*)&polymutecall->x1, (long*)&polymutecall->x2, (long*)&polymutecall->x3,
                          &polydepth,
                          &polyflag
                          );                               
              
              setUV4(polymutecall, 0, 0, 0, 31, 122, 0, 122, 31); // 8 diff (normaly 263 but can't go higher than 255, so 263-255 = 8)
                  
  
              addPrim(ot[db], polymutecall);                       
              
              nextpri += sizeof(POLY_FT4);    
            }

            if (camera == 0) {
                makepoly(6);

                if (GFactivated == 1) {
                    makepoly(5);
                }

                if (dead == 0 && fivetosixamframes == 0) {

                    if (pad & PADRdown || pad >> 16 & PADRdown) {speedoffice = 6;} else {speedoffice = 3;}

                    if(pad & PADLleft || pad >> 16 & PADLleft && twoplayermode == 1) {
                        if (MovVectorofficemiddle.vx < 80) {
                            MovVectorBB.vx = MovVectorBB.vx + speedoffice;
                            MovVectorGF.vx = MovVectorGF.vx + speedoffice;
                            MovVectorofficemiddle.vx = MovVectorofficemiddle.vx + speedoffice;
                            MovVectorofficeright1.vx = MovVectorofficeright1.vx + speedoffice;
                            MovVectorofficegolden.vx = MovVectorofficegolden.vx + speedoffice;
                            MovVectorofficefront.vx = MovVectorofficefront.vx + speedoffice;
                            MovVectorofficefronttoybonnie.vx = MovVectorofficefronttoybonnie.vx + speedoffice;
                            MovVectorhallway2.vx = MovVectorhallway2.vx + speedoffice;
                            MovVectorhallway.vx = MovVectorhallway.vx + speedoffice;
                            MovVectorhallway3.vx = MovVectorhallway3.vx + speedoffice;
                            MovVectorhallway3bis.vx = MovVectorhallway3bis.vx + speedoffice;
                            MovVectorhallway4.vx = MovVectorhallway4.vx + speedoffice;
                            MovVectorhallway5.vx = MovVectorhallway5.vx + speedoffice;
                            MovVectortablemiddle.vx = MovVectortablemiddle.vx + speedoffice;
                            MovVectorRvent.vx = MovVectorRvent.vx + speedoffice;
                            MovVectorLvent.vx = MovVectorLvent.vx + speedoffice;
                            MovVectormanglehanging.vx = MovVectormanglehanging.vx + speedoffice;
                        }
                    } // left ;)
                    if(pad & PADLright || pad >> 16 & PADLright && twoplayermode == 1) {
                        if (MovVectorofficemiddle.vx > -110) {
                            MovVectorBB.vx = MovVectorBB.vx - speedoffice;
                            MovVectorGF.vx = MovVectorGF.vx - speedoffice;
                            MovVectorofficemiddle.vx = MovVectorofficemiddle.vx - speedoffice;
                            MovVectorofficegolden.vx = MovVectorofficegolden.vx - speedoffice;
                            MovVectorhallway2.vx = MovVectorhallway2.vx - speedoffice;
                            MovVectorhallway.vx = MovVectorhallway.vx - speedoffice;
                            MovVectorhallway3.vx = MovVectorhallway3.vx - speedoffice;
                            MovVectorhallway3bis.vx = MovVectorhallway3bis.vx - speedoffice;
                            MovVectorhallway4.vx = MovVectorhallway4.vx - speedoffice;
                            MovVectorhallway5.vx = MovVectorhallway5.vx - speedoffice;
                            MovVectorofficefront.vx = MovVectorofficefront.vx - speedoffice;
                            MovVectorofficefronttoybonnie.vx = MovVectorofficefronttoybonnie.vx - speedoffice;
                            MovVectorRvent.vx = MovVectorRvent.vx - speedoffice;
                            MovVectorLvent.vx = MovVectorLvent.vx - speedoffice;
                            MovVectortablemiddle.vx = MovVectortablemiddle.vx - speedoffice;
                            MovVectormanglehanging.vx = MovVectormanglehanging.vx - speedoffice;
                        } else {
                            MovVectorofficemiddle.vx = -110;
                        }
                    } // right :) 
                }
            }
            if (camera == 1) {     
              if (night != 725255 && fivetosixamframes == 0) {

                  //camera's grey or green
                  polycamgreyogreen = (POLY_F4 *)nextpri;     
                          
                  RotMatrix(&RotVectorpolycamgreyogreen, &PolyMatrixpolycamgreyogreen);    
                  TransMatrix(&PolyMatrixpolycamgreyogreen, &MovVectorpolycamgreyogreen);
                  ScaleMatrix(&PolyMatrixpolycamgreyogreen, &ScaleVectorpolycamWoutline);  
                  
                  SetRotMatrix(&PolyMatrixpolycamgreyogreen);            
                  SetTransMatrix(&PolyMatrixpolycamgreyogreen);          
                  
                  setPolyF4(polycamgreyogreen);                          
                  
                  RotTransPers4(
                              &VertPospolycamgreyogreen[0],      &VertPospolycamgreyogreen[1],      &VertPospolycamgreyogreen[2],      &VertPospolycamgreyogreen[3],
                              (long*)&polycamgreyogreen->x0, (long*)&polycamgreyogreen->x1, (long*)&polycamgreyogreen->x2, (long*)&polycamgreyogreen->x3,
                              &polydepth,
                              &polyflag
                              );                               

                  addPrim(ot[db], polycamgreyogreen);        

                  setRGB0(polycamgreyogreen, 157, 184, 3);    
                  
                  nextpri += sizeof(POLY_F4);                
 
                  if (phoneguytalkingconst - 1620 < phoneguytalking && mutedcall == 0) {
                    polymutecall = (POLY_FT4 *)nextpri;                 
                            
                    RotMatrix(&RotVectormutecall, &PolyMatrixmutecall);    
                    TransMatrix(&PolyMatrixmutecall, &MovVectormutecall);  
                    ScaleMatrix(&PolyMatrixmutecall, &ScaleVectormutecall);
                    
                    SetRotMatrix(&PolyMatrixmutecall);                  
                    SetTransMatrix(&PolyMatrixmutecall);                
                    
                    setClut(polymutecall, 960, 200);
        
                          setRGB0(polymutecall, 128, 128, 128); 

                    setPolyFT4(polymutecall);                           
                    
                    polymutecall->tpage = getTPage(mutecall.mode&0x3, 0, 704, 256); 
                    
                    
                    RotTransPers4(
                                &VertPosmutecall[0],      &VertPosmutecall[1],      &VertPosmutecall[2],      &VertPosmutecall[3],
                                (long*)&polymutecall->x0, (long*)&polymutecall->x1, (long*)&polymutecall->x2, (long*)&polymutecall->x3,
                                &polydepth,
                                &polyflag
                                );                               
                    
                    setUV4(polymutecall, 0, 0, 0, 31, 122, 0, 122, 31); // 8 diff (normaly 263 but can't go higher than 255, so 263-255 = 8)
                        
        
                    addPrim(ot[db], polymutecall);                       
                    
                    nextpri += sizeof(POLY_FT4);    
                  }

                  if (dangerlevel > 0 && ismusicboxatzero == 0) {  
                      //first
                      polydanger = (POLY_FT4 *)nextpri;                 
                              
                      RotMatrix(&RotVectordanger, &PolyMatrixdanger);    
                      TransMatrix(&PolyMatrixdanger, &MovVectordanger2);  
                      ScaleMatrix(&PolyMatrixdanger, &ScaleVectordanger2);
                      
                      SetRotMatrix(&PolyMatrixdanger);                  
                      SetTransMatrix(&PolyMatrixdanger);                
                      
                      setClut(polydanger, 960, 201);

                      setPolyFT4(polydanger);         

                      setRGB0(polydanger, 128, 128, 128);                  
                      
                      polydanger->tpage = getTPage(danger.mode&0x3, 0, 768, 256); 
                      
                      
                      RotTransPers4(
                                  &VertPosdanger[0],      &VertPosdanger[1],      &VertPosdanger[2],      &VertPosdanger[3],
                                  (long*)&polydanger->x0, (long*)&polydanger->x1, (long*)&polydanger->x2, (long*)&polydanger->x3,
                                  &polydepth,
                                  &polyflag
                                  );                               
                      
                      setUV4(polydanger, 0, 0, 0, 29, 34, 0, 34, 29);
                          

                      addPrim(ot[db], polydanger);                       
                      
                      nextpri += sizeof(POLY_FT4);    
                  }

                  //Layout                
                  polylayout = (POLY_FT4 *)nextpri;              
                          
                  RotMatrix(&RotVectorlayout, &PolyMatrixlayout);
                  TransMatrix(&PolyMatrixlayout, &MovVectorlayout);  
                  ScaleMatrix(&PolyMatrixlayout, &ScaleVectorlayout);
                  
                  SetRotMatrix(&PolyMatrixlayout);                   
                  SetTransMatrix(&PolyMatrixlayout);                 
                  
                  setPolyFT4(polylayout);                     
                  setClut(polylayout,960,196);       
                  
                  polylayout->tpage = getTPage(layout.mode&0x3, 0, 640, 0); 
                  
                  if (fivetosixamframes == 0) {
                    setRGB0(polylayout, 128, 128, 128);    
                  }     
                  
                  RotTransPers4(
                              &VertPoslayout[0],      &VertPoslayout[1],      &VertPoslayout[2],      &VertPoslayout[3],
                              (long*)&polylayout->x0, (long*)&polylayout->x1, (long*)&polylayout->x2, (long*)&polylayout->x3,
                              &polydepth,
                              &polyflag
                              );                               
                  
                  setUV4(polylayout, 0, 0, 0, 229, 229, 0, 229, 229);  
                      
                  addPrim(ot[db], polylayout);                  
                  
                  nextpri += sizeof(POLY_FT4);  

                  if (curcam[0] == '1' && curcam[1] == '1') {   
                    //timer
                    polytimer = (POLY_FT4 *)nextpri;              
                            
                    RotMatrix(&RotVectortimer, &PolyMatrixtimer);    
                    TransMatrix(&PolyMatrixtimer, &MovVectortimer);  
                    ScaleMatrix(&PolyMatrixtimer, &ScaleVectortimer);
                    
                    SetRotMatrix(&PolyMatrixtimer);                    
                    SetTransMatrix(&PolyMatrixtimer);                  
                    
                    setPolyFT4(polytimer);                  

                    setClut(polytimer,960,192);     

                    polytimer->tpage = getTPage(timermusicbox.mode&0x3, 0, 832, 256); 

                    OTz = RotTransPers4(
                                &VertPostimer[0],      &VertPostimer[1],      &VertPostimer[2],      &VertPostimer[3],
                                (long*)&polytimer->x0, (long*)&polytimer->x1, (long*)&polytimer->x2, (long*)&polytimer->x3,
                                &polydepth,
                                &polyflag
                                );                   

                    setUV4(polytimer, 0, 0, 0, 54, 54, 0, 54, 54);                
                    
                    addPrim(ot[db], polytimer);                  
                    
                    nextpri += sizeof(POLY_FT4); 

                  }
                    //icon for camera
                    if (animatronicscamera[0] == 2) {
                        //FREDDY
                        polyfreddy = (POLY_F4 *)nextpri;               
                        
                                
                        RotMatrix(&RotVectorfreddy, &PolyMatrixfreddy);
                        TransMatrix(&PolyMatrixfreddy, &MovVectorfreddy);  
                        ScaleMatrix(&PolyMatrixfreddy, &ScaleVectorfreddy);
                        
                        SetRotMatrix(&PolyMatrixfreddy);                   
                        SetTransMatrix(&PolyMatrixfreddy);                 
                        
                        setPolyF4(polyfreddy);                             
                        
                        RotTransPers4(
                                    &VertPosfreddy[0],      &VertPosfreddy[1],      &VertPosfreddy[2],      &VertPosfreddy[3],
                                    (long*)&polyfreddy->x0, (long*)&polyfreddy->x1, (long*)&polyfreddy->x2, (long*)&polyfreddy->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        addPrim(ot[db], polyfreddy);       
                        setRGB0(polyfreddy, 67, 43, 19);              
                        
                        nextpri += sizeof(POLY_F4);                    
                    }
                    if (animatronicscamera[1] == 2) {
                        //BONNIE 
                        polybonnie = (POLY_F4 *)nextpri;           
                                
                        RotMatrix(&RotVectorbonnie, &PolyMatrixbonnie);
                        TransMatrix(&PolyMatrixbonnie, &MovVectorbonnie);  
                        ScaleMatrix(&PolyMatrixbonnie, &ScaleVectorbonnie);
                        
                        SetRotMatrix(&PolyMatrixbonnie);                   
                        SetTransMatrix(&PolyMatrixbonnie);                 
                        
                        setPolyF4(polybonnie);                             
                        
                        RotTransPers4(
                                    &VertPosbonnie[0],      &VertPosbonnie[1],      &VertPosbonnie[2],      &VertPosbonnie[3],
                                    (long*)&polybonnie->x0, (long*)&polybonnie->x1, (long*)&polybonnie->x2, (long*)&polybonnie->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        
                        addPrim(ot[db], polybonnie);            
                        setRGB0(polybonnie, 15, 38, 128);                   
                        
                        nextpri += sizeof(POLY_F4);                    
                    }
                    if (animatronicscamera[2] == 2) {
                        //CHICA
                        polychica = (POLY_F4 *)nextpri;                
                        
                                
                        RotMatrix(&RotVectorchica, &PolyMatrixchica);  
                        TransMatrix(&PolyMatrixchica, &MovVectorchica);
                        ScaleMatrix(&PolyMatrixchica, &ScaleVectorchica);
                        
                        SetRotMatrix(&PolyMatrixchica);                  
                        SetTransMatrix(&PolyMatrixchica);                
                        
                        setPolyF4(polychica);                            
                        
                        RotTransPers4(
                                    &VertPoschica[0],      &VertPoschica[1],      &VertPoschica[2],      &VertPoschica[3],
                                    (long*)&polychica->x0, (long*)&polychica->x1, (long*)&polychica->x2, (long*)&polychica->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        
                        addPrim(ot[db], polychica);                  
                        setRGB0(polychica, 151, 124, 15);                
                        
                        nextpri += sizeof(POLY_F4);               
                    }
                    if (animatronicscamera[3] == 2) {     
                        //FOXY
                        polyfoxy = (POLY_F4 *)nextpri;                
                                
                        RotMatrix(&RotVectorfoxy, &PolyMatrixfoxy);    
                        TransMatrix(&PolyMatrixfoxy, &MovVectorfoxy);  
                        ScaleMatrix(&PolyMatrixfoxy, &ScaleVectorfoxy);
                        
                        SetRotMatrix(&PolyMatrixfoxy);                 
                        SetTransMatrix(&PolyMatrixfoxy);               
                        
                        setPolyF4(polyfoxy);                           
                        
                        OTz = RotTransPers4(
                                    &VertPosfoxy[0],      &VertPosfoxy[1],      &VertPosfoxy[2],      &VertPosfoxy[3],
                                    (long*)&polyfoxy->x0, (long*)&polyfoxy->x1, (long*)&polyfoxy->x2, (long*)&polyfoxy->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        
                        addPrim(ot[db], polyfoxy);                     
                        
                        nextpri += sizeof(POLY_F4);            

                        setRGB0(polyfoxy, 138, 11, 11);   
                    }
                    if (animatronicscamera[5] == 2) {
                        //toyBONNIE 
                        polytoybonnie = (POLY_F4 *)nextpri;           
                                
                        RotMatrix(&RotVectortoybonnie, &PolyMatrixtoybonnie);
                        TransMatrix(&PolyMatrixtoybonnie, &MovVectortoybonnie);  
                        ScaleMatrix(&PolyMatrixtoybonnie, &ScaleVectortoybonnie);
                        
                        SetRotMatrix(&PolyMatrixtoybonnie);                   
                        SetTransMatrix(&PolyMatrixtoybonnie);                 
                        
                        setPolyF4(polytoybonnie);                             
                        
                        RotTransPers4(
                                    &VertPostoybonnie[0],      &VertPostoybonnie[1],      &VertPostoybonnie[2],      &VertPostoybonnie[3],
                                    (long*)&polytoybonnie->x0, (long*)&polytoybonnie->x1, (long*)&polytoybonnie->x2, (long*)&polytoybonnie->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        
                        setRGB0(polytoybonnie, 70, 194, 255);          

                        addPrim(ot[db], polytoybonnie);                   
                        
                        nextpri += sizeof(POLY_F4);  
                    }
                    if (animatronicscamera[4] == 2) {
                        //TOYFREDDY
                        polytoyfreddy = (POLY_F4 *)nextpri;               
                        
                                
                        RotMatrix(&RotVectortoyfreddy, &PolyMatrixtoyfreddy);
                        TransMatrix(&PolyMatrixtoyfreddy, &MovVectortoyfreddy);  
                        ScaleMatrix(&PolyMatrixtoyfreddy, &ScaleVectortoyfreddy);
                        
                        SetRotMatrix(&PolyMatrixtoyfreddy);                   
                        SetTransMatrix(&PolyMatrixtoyfreddy);                 
                        
                        setPolyF4(polytoyfreddy);                             
                        
                        RotTransPers4(
                                    &VertPostoyfreddy[0],      &VertPostoyfreddy[1],      &VertPostoyfreddy[2],      &VertPostoyfreddy[3],
                                    (long*)&polytoyfreddy->x0, (long*)&polytoyfreddy->x1, (long*)&polytoyfreddy->x2, (long*)&polytoyfreddy->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        addPrim(ot[db], polytoyfreddy);         

                        setRGB0(polytoyfreddy, 191, 96, 49);                
                        
                        nextpri += sizeof(POLY_F4);                    
                    }
                    if (animatronicscamera[6] == 2) {
                        //toyCHICA
                        polytoychica = (POLY_F4 *)nextpri;                
                        
                                
                        RotMatrix(&RotVectortoychica, &PolyMatrixtoychica);  
                        TransMatrix(&PolyMatrixtoychica, &MovVectortoychica);
                        ScaleMatrix(&PolyMatrixtoychica, &ScaleVectortoychica);
                        
                        SetRotMatrix(&PolyMatrixtoychica);                  
                        SetTransMatrix(&PolyMatrixtoychica);                
                        
                        setPolyF4(polytoychica);                            
                        
                        RotTransPers4(
                                    &VertPostoychica[0],      &VertPostoychica[1],      &VertPostoychica[2],      &VertPostoychica[3],
                                    (long*)&polytoychica->x0, (long*)&polytoychica->x1, (long*)&polytoychica->x2, (long*)&polytoychica->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        
                        addPrim(ot[db], polytoychica);          

                        setRGB0(polytoychica, 240, 240, 25);               
                        
                        nextpri += sizeof(POLY_F4);            
                    }
                    if (animatronicscamera[7] == 2) {
                        //mangle
                        polymangle = (POLY_F4 *)nextpri;                
                                
                        RotMatrix(&RotVectormangle, &PolyMatrixmangle);    
                        TransMatrix(&PolyMatrixmangle, &MovVectormangle);  
                        ScaleMatrix(&PolyMatrixmangle, &ScaleVectormangle);
                        
                        SetRotMatrix(&PolyMatrixmangle);                 
                        SetTransMatrix(&PolyMatrixmangle);               
                        
                        setPolyF4(polymangle);                           
                        
                        OTz = RotTransPers4(
                                    &VertPosmangle[0],      &VertPosmangle[1],      &VertPosmangle[2],      &VertPosmangle[3],
                                    (long*)&polymangle->x0, (long*)&polymangle->x1, (long*)&polymangle->x2, (long*)&polymangle->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        
                        addPrim(ot[db], polymangle);               

                        setRGB0(polymangle, 201, 118, 118);              
                        
                        nextpri += sizeof(POLY_F4);                   
                    }
                    if (animatronicscamera[8] == 2) {
                        //Golden freddy
                        polygoldenf = (POLY_F4 *)nextpri;              
                                
                        RotMatrix(&RotVectorgoldenf, &PolyMatrixgoldenf);    
                        TransMatrix(&PolyMatrixgoldenf, &MovVectorgoldenf);  
                        ScaleMatrix(&PolyMatrixgoldenf, &ScaleVectorgoldenf);
                        
                        SetRotMatrix(&PolyMatrixgoldenf);                    
                        SetTransMatrix(&PolyMatrixgoldenf);                  
                        
                        setPolyF4(polygoldenf);                          
                        setRGB0(polygoldenf,204,204,0);
                        OTz = RotTransPers4(
                                    &VertPosgoldenf[0],      &VertPosgoldenf[1],      &VertPosgoldenf[2],      &VertPosgoldenf[3],
                                    (long*)&polygoldenf->x0, (long*)&polygoldenf->x1, (long*)&polygoldenf->x2, (long*)&polygoldenf->x3,
                                    &polydepth,
                                    &polyflag
                                    );                                 
                        
                        addPrim(ot[db], polygoldenf);                  
                        
                        nextpri += sizeof(POLY_F4);                 
                    }   
                }  
            }
                if (blinkicon < 61) {blinkicon++;}
                if (blinkicon == 60) {blinkicon = 0;}
                //need to add golden freddy hallway 
                if (freddylocation > 2 || foxylocation > 0 || toyfreddylocation > 1 || bonnielocation > 3 || chicalocation > 2 || toybonnielocation > 3 || toychicalocation > 3 || manglelocation > 3 || BBlocation > 3 || puppetlocation > 3) { if (weirdnight == 0 && AM != 6) {triggeralarm = 1;}} else {triggeralarm = 0;}
                if (BBlocation == 6) {BBlol = 1;} else {BBlol = 0;}

                if (triggeralarm == 1 && nightwon == 0) {
                  if (SpuGetKeyStatus(SPU_13CH) == SPU_OFF) {
                    SpuSetKey(SPU_ON, SPU_13CH);
                  }
                } else {
                  SpuSetKey(SPU_OFF, SPU_13CH);
                }

                if (BBlol && nightwon == 0) {
                    if (SpuGetKeyStatus(SPU_17CH) == SPU_OFF) {
                        SpuSetKey(SPU_ON, SPU_17CH);
                    }
                } else {
                    SpuSetKey(SPU_OFF, SPU_17CH);
                }

                if (BBlolonce && nightwon == 0) {
                    Ran(10);
                    if (RAN < 5) {
                            SpuSetKey(SPU_ON, SPU_15CH);
                    } else {
                            SpuSetKey(SPU_ON, SPU_16CH);
                    }
                    BBlolonce = 0;
                }

                //Don't know any other ways to store that piece of (shit) code
                //PATH
                if (freddylocation == 0) { //Part and Service
                    MovVectorfreddy.vx = -34; 
                    MovVectorfreddy.vy = -42;
                    if (curcam[0] == '0' && curcam[1] == '8') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[0] = 2;
                      } else {
                        animatronicscamera[0] = 1;
                      }
                    } else {
                        animatronicscamera[0] = 0;
                    }
                }
                if (freddylocation == 1) { // Main hall
                    MovVectorfreddy.vx = -10; 
                    MovVectorfreddy.vy = -35;
                    if (curcam[0] == '0' && curcam[1] == '7') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[0] = 2;
                      } else {
                        animatronicscamera[0] = 1;
                      }
                    } else {
                        animatronicscamera[0] = 0;
                    }
                }
                if (freddylocation == 2) { // Party Room 3
                    MovVectorfreddy.vx = -38; 
                    MovVectorfreddy.vy = -15;
                    if (curcam[0] == '0' && curcam[1] == '3') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[0] = 2;
                      } else {
                        animatronicscamera[0] = 1;
                      }
                    } else {
                        animatronicscamera[0] = 0;
                    }
                }
                if (freddylocation == 3) { // Hallway
                    animatronicscamera[0] = 0;
                }
                if (freddylocation == 4) { // Office
                    animatronicscamera[0] = 0;
                }
                if (bonnielocation == 0) { //Part and Service
                    MovVectorbonnie.vx = -43; 
                    MovVectorbonnie.vy = -41;
                    if (curcam[0] == '0' && curcam[1] == '8') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[1] = 2;
                      } else {
                        animatronicscamera[1] = 1;
                      }
                    } else {
                        animatronicscamera[1] = 0;
                    }
                }
                if (bonnielocation == 1) { // Main hall
                    MovVectorbonnie.vx = -20; 
                    MovVectorbonnie.vy = -35;
                    if (curcam[0] == '0' && curcam[1] == '7') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[1] = 2;
                      } else {
                        animatronicscamera[1] = 1;
                      }
                    } else {
                        animatronicscamera[1] = 0;
                    }
                }
                if (bonnielocation == 2) { // Hallway
                    animatronicscamera[1] = 0;
                }
                if (bonnielocation == 3) { // Party room 1
                    MovVectorbonnie.vx = 50;
                    MovVectorbonnie.vy = -49;
                    if (curcam[0] == '0' && curcam[1] == '9') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[1] = 2;
                      } else {
                        animatronicscamera[1] = 1;
                      }
                    } else {
                        animatronicscamera[1] = 0;     
                    }
                }
                if (bonnielocation == 4) { // L. Vent
                    MovVectorbonnie.vx = -46;
                    MovVectorbonnie.vy = 33;
                    if (curcam[0] == '0' && curcam[1] == '5') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[1] = 2;
                      } else {
                        animatronicscamera[1] = 1;
                      }
                    } else {
                        animatronicscamera[1] = 0;
                    }
                }
                if (bonnielocation == 5) { // Office
                    animatronicscamera[1] = 0;
                }
                if (chicalocation == 0) { // Part and Service

                    MovVectorchica.vx = -41; 
                    MovVectorchica.vy = -36;
                    if (curcam[0] == '0' && curcam[1] == '8') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[2] = 2;
                      } else {
                        animatronicscamera[2] = 1;
                      }
                    } else {
                        animatronicscamera[2] = 0;
                    }
                }
                if (chicalocation == 1) { // Party Room 4
                    MovVectorchica.vx = 10;
                    MovVectorchica.vy = -13;
                    if (curcam[0] == '0' && curcam[1] == '4') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[2] = 2;
                      } else {
                        animatronicscamera[2] = 1;
                      }
                    } else {
                        animatronicscamera[2] = 0;
                    }
                }
                if (chicalocation == 2) { // Party Room 2
                    MovVectorchica.vx = 5;
                    MovVectorchica.vy = 12;
                    if (curcam[0] == '0' && curcam[1] == '2') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[2] = 2;
                      } else {
                        animatronicscamera[2] = 1;
                      }
                    } else {
                        animatronicscamera[2] = 0;
                    }

                }
                if (chicalocation == 3) { // R.Vent
                    MovVectorchica.vx = 10;
                    MovVectorchica.vy = 33;
                    if (curcam[0] == '0' && curcam[1] == '6') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[2] = 2;
                      } else {
                        animatronicscamera[2] = 1;
                      }
                    } else {
                        animatronicscamera[2] = 0;
                    }

                }
                if (chicalocation == 4) { // Office
                    animatronicscamera[2] = 0;
                }

                //foxy's not here

                if (toyfreddylocation == 0) { //Stage
                        MovVectortoyfreddy.vx = 41; 
                        MovVectortoyfreddy.vy = -45;
                    if (curcam[0] == '0' && curcam[1] == '9') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[4] = 2;
                      } else {
                        animatronicscamera[4] = 1;
                      }
                    } else {
                        animatronicscamera[4] = 0;
                    }
                }
                if (toyfreddylocation == 1) { //Game area
                    MovVectortoyfreddy.vx = 28;
                    MovVectortoyfreddy.vy = -30;
                    if (curcam[0] == '1' && curcam[1] == '0') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[4] = 2;
                      } else {
                        animatronicscamera[4] = 1;
                      }
                    } else {
                        animatronicscamera[4] = 0;
                    }
                }
                if (toyfreddylocation > 1) { //Hallway (far) 2, hallway (closer) 3, in your office 4
                    animatronicscamera[4] = 0;
                }
                if (toybonnielocation == 0) { //Stage
                    MovVectortoybonnie.vx = 32;
                    MovVectortoybonnie.vy = -49;
                    if (curcam[0] == '0' && curcam[1] == '9') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[5] = 2;
                      } else {
                        animatronicscamera[5] = 1;
                      }
                    } else {
                        animatronicscamera[5] = 0;
                    }
                }
                if (toybonnielocation == 1) { //Party room 3
                    MovVectortoybonnie.vx = -43;
                    MovVectortoybonnie.vy = -15;
                    if (curcam[0] == '0' && curcam[1] == '3') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[5] = 2;
                      } else {
                        animatronicscamera[5] = 1;
                      }
                    } else {
                        animatronicscamera[5] = 0;
                    }
                }
                if (toybonnielocation == 2) { //Party room 4
                    MovVectortoybonnie.vx = 5;
                    MovVectortoybonnie.vy = -11;
                    if (curcam[0] == '0' && curcam[1] == '4') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[5] = 2;
                      } else {
                        animatronicscamera[5] = 1;
                      }
                    } else {
                        animatronicscamera[5] = 0;
                    }
                }
                if (toybonnielocation == 3) { //Party room 2
                    MovVectortoybonnie.vx = 10;
                    MovVectortoybonnie.vy = 12;
                    if (curcam[0] == '0' && curcam[1] == '2') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[5] = 2;
                      } else {
                        animatronicscamera[5] = 1;
                      }
                    } else {
                        animatronicscamera[5] = 0;
                    }
                }
                if (toybonnielocation == 4) { //R. Vent (in)
                    MovVectortoybonnie.vx = 10;
                    MovVectortoybonnie.vy = 33;
                    if (curcam[0] == '0' && curcam[1] == '6') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[5] = 2;
                      } else {
                        animatronicscamera[5] = 1;
                      }
                    } else {
                        animatronicscamera[5] = 0;
                    }
                }
                if (toybonnielocation == 5) { //R. Vent (out)
                    animatronicscamera[5] = 0;
                }
                if (toybonnielocation == 6) { //Office
                    animatronicscamera[5] = 0;
                }

                if (toychicalocation == 0) { //Stage
                    MovVectortoychica.vx = 50;
                    MovVectortoychica.vy = -49;
                    if (curcam[0] == '0' && curcam[1] == '9') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[6] = 2;
                      } else {
                        animatronicscamera[6] = 1;
                      }
                    } else {
                        animatronicscamera[6] = 0;     
                    }
                }
                if (toychicalocation == 1) { //Main hall
                    MovVectortoychica.vx = -5;
                    MovVectortoychica.vy = -33;
                    if (curcam[0] == '0' && curcam[1] == '7') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[6] = 2;
                      } else {
                        animatronicscamera[6] = 1;
                      }
                    } else {
                        animatronicscamera[6] = 0;           
                    }
                }
                if (toychicalocation == 2) { //hallway outside
                    animatronicscamera[6] = 0;   
                }
                if (toychicalocation == 3) { //Party room 1
                    MovVectortoychica.vx = -46;
                    MovVectortoychica.vy = 12;
                    if (curcam[0] == '0' && curcam[1] == '1') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[6] = 2;
                      } else {
                        animatronicscamera[6] = 1;
                      }
                    } else {
                        animatronicscamera[6] = 0;           
                    }
                }
                if (toychicalocation == 4) { //L.Vent (in)
                    MovVectortoychica.vx = -46;
                    MovVectortoychica.vy = 33;
                    if (curcam[0] == '0' && curcam[1] == '5') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[6] = 2;
                      } else {
                        animatronicscamera[6] = 1;
                      }
                    } else {
                        animatronicscamera[6] = 0;
                    }
                }
                if (toychicalocation == 5){ //L.Vent (out)
                    animatronicscamera[6] = 0;
                }

                //BB is not here either

                if (manglelocation == 0) { //Kids cove
                    MovVectormangle.vx = 38;
                    MovVectormangle.vy = 21;

                    if (curcam[0] == '1' && curcam[1] == '2') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[7] = 2;
                      } else {
                        animatronicscamera[7] = 1;
                      }
                    } else {
                        animatronicscamera[7] = 0;
                    }
                }
                if (manglelocation == 1) { //Prize corner
                    MovVectormangle.vx = 58;
                    MovVectormangle.vy = -5;
                    if (curcam[0] == '1' && curcam[1] == '1') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[7] = 2;
                      } else {
                        animatronicscamera[7] = 1;
                      }
                    } else {
                        animatronicscamera[7] = 0;    
                    }
                }
                if (manglelocation == 2) { //Game area
                    MovVectormangle.vx = 25;
                    MovVectormangle.vy = -10;
                    if (curcam[0] == '1' && curcam[1] == '0') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[7] = 2;
                      } else {
                        animatronicscamera[7] = 1;
                      }
                    } else {
                        animatronicscamera[7] = 0;    
                    }
                }
                if (manglelocation == 3) { //Main Hall
                    MovVectormangle.vx = 0;
                    MovVectormangle.vy = -36;
                    if (curcam[0] == '0' && curcam[1] == '7') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[7] = 2;
                      } else {
                        animatronicscamera[7] = 1;
                      }
                    } else {
                        animatronicscamera[7] = 0;
                    }
                }
                //apparently mangle can be seen on cam 01
                if (manglelocation == 4) { //Hallway
                    animatronicscamera[7] = 0;
                }
                //apparently mangle can be seen on cam 01
                if (manglelocation == 5) { //Party Room 2
                    MovVectormangle.vx = 0;
                    MovVectormangle.vy = 6;
                    if (curcam[0] == '0' && curcam[1] == '2') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[7] = 2;
                      } else {
                        animatronicscamera[7] = 1;
                      }
                    } else {
                        animatronicscamera[7] = 0;
                    }
                }
                if (manglelocation == 6) { //R. Vent (in)
                    MovVectormangle.vx = 10;
                    MovVectormangle.vy = 33;
                    if (curcam[0] == '0' && curcam[1] == '6') {
                      if (blinkicon > 30 || radar == 1) {
                        animatronicscamera[7] = 2;
                      } else {
                        animatronicscamera[7] = 1;
                      }
                    } else {
                        animatronicscamera[7] = 0;
                    }
                }
                if (manglelocation == 7 || manglelocation == 8) { //R. Vent (out)
                    animatronicscamera[7] = 0;
                }
                //Might do another route she can pick (hallway)
        }//Gameplay Screen
        if (menu == 3) { //Game over screen. ALWAYS BEGIN WITH THE STATIC
            if (staticframes > 1) {
                makepoly(15);
                if (staticframessheet == 8) {
                    staticframessheet = 0;
                    MovVectorstatic.vx = MovVectorstatic.vx - 16;
                } else {
                    staticframessheet++;
                    MovVectorstatic.vx = MovVectorstatic.vx + 2;
                }
                if (staticframessheet == 0) {
                }
            }
            if (staticframes == 259) {
                LoadTexture(_binary_tim_static1_tim_start, &statics); 
                SpuSetKey(SPU_OFF, SPU_ALLCH);
            }
            if (staticframes == 2) {
              CdControlF(CdlPause,0);
              sample = 0;
            }
            if (staticframes < 1) {
                seedrandom++; //While testing Freddy, I realized that he took a very long time to CUM. So I put that to prevent having the same seed. Thank you, Freddy, for CUMING very lately (incrementing does not necessarily means taking longer to CUM)

                gameoverprint();

                makepoly(12);

                if (pad & PADstart) {
                    resetgame(0);
                    menu = 1;
                }
            } else{staticframes--;}
        }//Game over screen. ALWAYS BEGIN WITH THE STATIC
        FntFlush(-1); //Draw
        display(); //Always here        
    }
    return 0;
}
void timeFunc(void) {
    if (lighthall) {
        flashlightbattery--;
        if (flashlightbattery > 2000 && flashlightbattery < 3000) {batterypublic = 3;}
        if (flashlightbattery > 1000 && flashlightbattery < 2000) {batterypublic = 2;}
        if (flashlightbattery > 1000 && flashlightbattery < 2000) {batterypublic = 1;}
        if (flashlightbattery == 0) {LightFuncHall();}
    }
    if (onesecondvar == 0) {
        onesecondvar = 60;
    } else {onesecondvar--;}
      FrameCounter++;

      seedrandom = seedrandom + FrameCounter + camera; // This gonna be huge //camera for additional random
      srand(seedrandom);

      Glitch++;
      Glitch = Glitch + 3 * 8;
      if (Glitch > 1987) {Glitch = Glitch - 987;}

      if (FrameCounter == FrameCounterlimit) {
          AM++;
          if (AM == 13) {
              AM = 1;
          }
          FrameCounter = 0;
      }
      if (fanframes > 3) {fanframes = 0;} else {fanframes++;}
}
void resetgame(int hardreset) {
  if (debugging == 0) {
    if (hardreset == 1) {
      freddydifficulty = 0;
      bonniedifficulty = 0;
      chicadifficulty = 0;
      foxydifficulty = 0;
      BBdifficulty = 0;
      toyfreddydifficulty = 0;
      toybonniedifficulty = 0;
      toychicadifficulty = 0;
      mangledifficulty = 0;
      GFdifficulty = 0;
      puppetdifficulty = 0;

      musicboxunwidingvalue = 0;
      musicboxunwidingvaludemi = 0;
      musicboxunwidingvaluthird = -2;
    }

      musicboxtimer = 2000;

      freddylocation = 0;
      bonnielocation = 0;
      chicalocation = 0;
      foxylocation = 0;
      toyfreddylocation = 0;
      toybonnielocation = 0;
      toychicalocation = 0;
      manglelocation = 0;
      BBlocation = 0;
      BBlol = 0;
      puppetlocation = 0;

    GFactivated = 0;
    GFnotactivatedyet = 0;
    GFactivatedhallway = 0;
    GFscreamerhallway = 0;
    fadeGF = 128;
  }

    ismusicboxatzero = 0;

    foxyalterablevalue = 0;

    toychicaHere = 0;
    toybonnieHere = 0;
    mangleHere = 0;
    BBHere = 0;
    triggeralarm = 0;

    for (int i = 0; i < 4; i++){ if (officequeue[i] != 0){ officequeue[i] = 0;}}

    officequeuetimer = 0;

    cantlight = 0;
    cantlightR = 0;
    cantlightL = 0;

    side = 0; //0 is left, 1 is right

    ismaskon = 0;

    light1 = 0;
    light2 = 0;
    lightframe = 0;

    camera = 0;
    curcam[0] = '0';
    curcam[1] = '9';

    noisefootstep = 0;
    framenoisefootstep = 0;

    fivesecondframe = 600;

    mascottune = 0;
    musicmascottune = 1248;

    isalreadydead = 0;
    isalreadydeadlow = 0;
    framedeadpossi = 60;
    lastsecondsframes = 1800;

    screamersetsound = 0;
    screamerframes = 47;
    spriteframes = 2;
    spritesheet = 0;

    deadtoybonnie = 0;
    dead = 0;
    deadfrom = 0;
    spriteframesconst = 4;
    GFscaling = 1024;

    fadeoffice = 128;

    nightwon = 0;
    nextnightframes = 0;
    staticframessheet = 0;
    MovVectorstatic.vx = -40;

    staticframes = 300;

    ventbanging = 0;
    ventbangingframes = 0;

    AM = 12;
    FrameCounter = 0;

    mutedcall = 0;
}
void print(int number) {
    if (camera == 0) {
        if (number == 1) { //Basic debug (without access to camera)
            FntPrint("AM : %d, current RAN : %d", AM, RAN);  // print time
            if (side == 0) { //print lights
                FntPrint("\nleft Light: %d", light1);
            }
            if (side == 1) {
                FntPrint("\nRight Light: %d", light2);
            }
            FntPrint("\n\nphoneguytalking %d, ambiancechance %d, fivesecondframe %d", phoneguytalking, ambiancechance, fivesecondframe); //print cam     
        }
    }
    if (number == 3) { //Vanilla debug (with access to camera)
        if (camera == 0) {
            FntPrint("\n");
        }
        FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");  // For the text to go bottom LOL
        if (night != 725255) {
            FntPrint("%d AM \n", AM);  // print time
            if (flashlightbattery > 500 ) {FntPrint("Flash Battery %d \n", batterypublic);}
            if (flashlightbattery < 500 && flashlightbattery > 0) {
                if (blinkicon > 30) {
                    FntPrint("Flash Battery low \n");
                } else {FntPrint(" \n");
                }
            }
            FntPrint("Night %d \n", night);
        } else {
          if (phoneguytalking > 960) {
            FntPrint("Night ^') \n");
          }
        }
    }
    if (camera == 1 && number != 2) {
        FntPrint("Camera :               %s,%s", curcam, curcamname);  // print time
    }
    if (number == 2) { // OLD Animatronic debug (with access to camera)
        FntPrint("%d AM, IAD %d, RAN %d\n",AM, isalreadydead, RAN);
        FntPrint("OLD FlocFrame %d & location %d,",freddylocationframe, freddylocation);
        FntPrint("\nBLocFrame %d & location %d,", bonnielocationframe, bonnielocation);
        FntPrint("\nCLocFrame %d & location %d,\nFOlocFrame %d & location %d. ismaskon %d",chicalocationframe, chicalocation, foxylocationframe, foxylocation, ismaskon);
        FntPrint("\nFoxy : alterval %d, flashcount %d, fattackcount %d", foxyalterablevalue, flashlightcounter, foxyattackcounter);
        FntPrint("\nGF : Hlw %d, SCRhlw %d, OFFICE %d, notyet %d", GFactivatedhallway, GFscreamerhallway, GFactivated, GFnotactivatedyet);
        FntPrint("\nOLD AI F %d, B %d, C %d,Fo %d.\nTOY AI F %d, B %d, C %d, M %d.",freddydifficulty, bonniedifficulty, chicadifficulty, foxydifficulty, toyfreddydifficulty, toybonniedifficulty, toychicadifficulty, mangledifficulty);
    }
    if (number == 4) { // TOY Animatronic debug (with access to camera)
        FntPrint("%d AM, IAD %d, RAN %d, musicbox %d, pos %d, %d\n",AM, isalreadydead, RAN, musicboxtimer, MovVectorofficemiddle, flashlightbattery);
        FntPrint("TOY TFlocFrame %d & loc %d,",toyfreddylocationframe, toyfreddylocation);
        FntPrint("\nTBLocFrame %d & loc %d %d,", toybonnielocationframe, toybonnielocation, toybonnieframevent);
        FntPrint("\nTCLocFrame %d & loc %d,\nMlocFrame %d & loc %d. Mattack %d\n",toychicalocationframe, toychicalocation, manglelocationframe, manglelocation, mangleattack);
        FntPrint("BBLocFrame %d & loc %d sound %d %d\n",BBlocationframe, BBlocation, ambiancesound, ambiancechance);
        FntPrint("OLD AI F %d, B %d, C %d,Fo %d.\nTOY AI F %d, B %d, C %d, M %d.",freddydifficulty, bonniedifficulty, chicadifficulty, foxydifficulty, toyfreddydifficulty, toybonniedifficulty, toychicadifficulty, mangledifficulty);
    }
    if (number == 5) { // Almost same then vanilla but with officequeue array and some things too
        FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");  // For the text to go bottom LOL
        if (night != 725255) {
          FntPrint("%d AM , RAN %d, musicbox %d\n", AM, RAN, musicboxtimer);  // print time
          FntPrint("Night %d \n", night);
          FntPrint("Queue array :  %d %d %d %d %d\n", officequeue[0], officequeue[1], officequeue[2], officequeue[3], officequeue[4]);
          FntPrint("Loc :  %d %d %d %d %d\n", freddylocation, bonnielocation, chicalocation, toyfreddylocation, toybonnielocation);
        } else {
          if (phoneguytalking > 960) {
            FntPrint("Night ^') \n");
          }
        }
  }
}
void printNightInfo(void) { //print night information (1st, 2nd, 3rd, etc)
    if (night == 1) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              1st  night", AM); 
    }
    if (night == 2) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              2nd  night", AM); 
    }
    if (night == 3) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              3rd  night", AM); 
    }
    if (night == 4) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              4th  night", AM);
    }
    if (night == 5) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              5th  night", AM);
    }
    if (night == 6) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              6th  night", AM);
    }
    if (night == 725255) {
        FntPrint("\n\n\n\n\n\n\n\n\n               `e:ç^ ¤*\n\n              @[#  night", AM);
    }
    if (customnightactivated == 1) {FntPrint("\n\n             Custom night");}  // debug time
    if (activatedmenudebug == 1) {FntPrint("\n\n              Debug Mode");}  // debug time
    if (cheating == 1) {FntPrint("\n\n            Cheat Activate");}  // cheat time
}
void menuselectionfunc(void) { //LONG asf lmaoo
    if (pad & PADLup) {
        if (limiterpadup == 0) {
            if (menuselection > 1) {
                menuselection--;
            }
            else {
                menuselection = menuselectionmax;
            }
            SpuSetKey(SPU_ON, SPU_03CH);
            limiterpadup = 1;
        }
    }
    if (pad & PADLdown) {
        if (limiterpaddown == 0) {
            if (menuselection < menuselectionmax) {
                menuselection++;
            }
            else {
                menuselection = 1;
            }
            SpuSetKey(SPU_ON, SPU_03CH);
            limiterpaddown = 1;
        }
    }
    if (!(pad & PADLright)) {limiterpadright = 0;}
    if (!(pad & PADLleft)) {limiterpadleft = 0;}
    if (!(pad & PADLdown)) {limiterpaddown = 0;}
    if (!(pad & PADLup)) {limiterpadup = 0;}
    if (!(pad & PADstart)) {limiterstart = 0;}
    if (!(pad & PADRdown)) {limiterbuttondown = 0;}

    if (maincustomnightmenu == 0 && extramenu == 0 && infoscreen == 0 && unlockssubmenu == 0 && AISetmenu == 0 && timermenu == 0 && advancedmenu == 0) {  
        if (menuselection == 1) {//"Starting" night
            if (pad & PADstart) {
                night = 1;
                helpwantedposter = 1;
            } 
        }

        if (menuselection == 2) { //Continue nights
            if (pad & PADstart) {
                loadingframe = 360;
                menu = 1;
            }//Or...
            if (pad & PADRup && pad & PADRright && pad & PADR1 && pad & PADL2 && activatedmenudebug == 0) //Activate debug !
            {
                activatedmenudebug = 1;
                menuselectionmax = menuselectionmax + 1;
            }
        }

        if (menuselection == 3) { //EXTRA MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 1;
                    menuselection = 1;
                    limiterstart++;
                    if (activatedmenudebug == 0) {
                        menuselectionmax = 5;
                    }
                    if (activatedmenudebug == 1) {
                        menuselectionmax = 7;
                    }
                }
            }
        }
        if (menuselection == 4) { //CUSTOM NIGHT MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    menuselection = 1;
                    menuselectionmax = 6;
                    limiterstart++;
                }
            }
        }

        if (activatedmenudebug == 1) {
            if (menuselection == 5) {
                if (pad & PADLright) {
                    if (limiterpadright == 0) {
                        printnumber++;
                        if (printnumber > 5) {printnumber = 1;}
                        limiterpadright = 1;
                    }
                }
                if (pad & PADLleft) {
                    if (limiterpadleft == 0) {
                        printnumber--;
                        if (printnumber < 1) {printnumber = 5;}
                        limiterpadleft = 1;
                    }
                }
            }
        }
    }

    if (maincustomnightmenu == 1) {
        if (menuselection == 1) {
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    night++;
                    if (night > 6) {night = 1;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    night--;
                    if (night < 1) {night = 6;}
                    limiterpadleft = 1;
                }
            } //Change night's var
        }

        if (menuselection == 2) { // AI SET MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 0;
                    AISetmenu = 1;
                    menuselection = 7;
                    menuselectionmax = 7;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 3) { // TIMER ETC MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 0;
                    timermenu = 1;
                    menuselection = 3;
                    menuselectionmax = 3;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 4) { // ADV MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 0;
                    advancedmenu = 1;
                    menuselection = 3;
                    menuselectionmax = 3;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 5) { // LAUNCH NIGHT
            if (pad & PADstart) {
              if (limiterstart == 0) {
                menu = 1;
                customnightactivated = 1;
              }
            }
        }
        if (menuselection == 6) { // RETURN TO MAIN MENU
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                    maincustomnightmenu = 0;
                    menuselection = 4;
                    limiterstart++;
                    if (activatedmenudebug == 0) {menuselectionmax = 4;}
                    else {menuselectionmax = 5;}
                }
            }
        }
    }
    if (AISetmenu == 1) {
        if (animatronicategorie == 1) {
            if (menuselection == 1) {
                if (pad & PADLright) { //Freddy
                    if (limiterpadright == 0) {
                        freddydifficulty++;
                        if (freddydifficulty > 20) {freddydifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Freddy
                    if (limiterpadleft == 0) {
                        freddydifficulty--;
                        if (freddydifficulty < 0) {freddydifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 2) {
                if (pad & PADLright) { //Bonnie
                    if (limiterpadright == 0) {
                        bonniedifficulty++;
                        if (bonniedifficulty > 20) {bonniedifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Bonnie
                    if (limiterpadleft == 0) {
                        bonniedifficulty--;
                        if (bonniedifficulty < 0) {bonniedifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 3) {
                if (pad & PADLright) { //Chica
                    if (limiterpadright == 0) {
                        chicadifficulty++;
                        if (chicadifficulty > 20) {chicadifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Chica
                    if (limiterpadleft == 0) {
                        chicadifficulty--;
                        if (chicadifficulty < 0) {chicadifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 4) {
                if (pad & PADLright) { //Foxy
                    if (limiterpadright == 0) {
                        foxydifficulty++;
                        if (foxydifficulty > 20) {foxydifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Foxy
                    if (limiterpadleft == 0) {
                        foxydifficulty--;
                        if (foxydifficulty < 0) {foxydifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
        }

        if (animatronicategorie == 2) {
            if (menuselection == 1) {
                if (pad & PADLright) { //Toy Freddy
                    if (limiterpadright == 0) {
                        toyfreddydifficulty++;
                        if (toyfreddydifficulty > 20) {toyfreddydifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Toy Freddy
                    if (limiterpadleft == 0) {
                        toyfreddydifficulty--;
                        if (toyfreddydifficulty < 0) {toyfreddydifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 2) {
                if (pad & PADLright) { //Toy Bonnie
                    if (limiterpadright == 0) {
                        toybonniedifficulty++;
                        if (toybonniedifficulty > 20) {toybonniedifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Toy Bonnie
                    if (limiterpadleft == 0) {
                        toybonniedifficulty--;
                        if (toybonniedifficulty < 0) {toybonniedifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 3) {
                if (pad & PADLright) { //Toy Chica
                    if (limiterpadright == 0) {
                        toychicadifficulty++;
                        if (toychicadifficulty > 20) {toychicadifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Toy Chica
                    if (limiterpadleft == 0) {
                        toychicadifficulty--;
                        if (toychicadifficulty < 0) {toychicadifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 4) {
                if (pad & PADLright) { //Toy Foxy (mangle)
                    if (limiterpadright == 0) {
                        mangledifficulty++;
                        if (mangledifficulty > 20) {mangledifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Toy Foxy (mangle)
                    if (limiterpadleft == 0) {
                        mangledifficulty--;
                        if (mangledifficulty < 0) {mangledifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
        }

        if (animatronicategorie == 3) {
            if (menuselection == 1) {
                if (pad & PADLright) { //BB
                    if (limiterpadright == 0) {
                        BBdifficulty++;
                        if (BBdifficulty > 20) {BBdifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //BB
                    if (limiterpadleft == 0) {
                        BBdifficulty--;
                        if (BBdifficulty < 0) {BBdifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 2) {
                if (pad & PADLright) { //Golden Freddy
                    if (limiterpadright == 0) {
                        GFdifficulty++;
                        if (GFdifficulty > 20) {GFdifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Golden Freddy
                    if (limiterpadleft == 0) {
                        GFdifficulty--;
                        if (GFdifficulty < 0) {GFdifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 3) {
                if (pad & PADRdown) { //Character level up ?
                    if (limiterbuttondown == 0) {
                      if (doescharlevelup == 0) {
                        doescharlevelup = 1;
                        doescharlevelupstr[0] = 'O';
                        doescharlevelupstr[1] = 'n';
                        doescharlevelupstr[2] = ' ';
                      } else {
                        doescharlevelup = 0;
                        doescharlevelupstr[0] = 'O';
                        doescharlevelupstr[1] = 'f';
                        doescharlevelupstr[2] = 'f';
                      }
                      limiterbuttondown = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
        }

        if (menuselection == 5) {
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    animatronicategorie--;
                    if (animatronicategorie < 1) {animatronicategorie = 1;}
                    limiterpadleft = 1;
                }
            }
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    animatronicategorie++;
                    if (animatronicategorie > 3) {animatronicategorie = 3;}
                    limiterpadright = 1;
                }
            }
        }

        if (menuselection == 6) {
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    presetselector--;
                    if (presetselector < 1) {presetselector = 16;}
                    limiterpadleft = 1;
                }
                SpuSetKey(SPU_ON, SPU_10CH);
            }
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    presetselector++;
                    if (presetselector > 16) {presetselector = 1;}
                    limiterpadright = 1;
                }
                SpuSetKey(SPU_ON, SPU_10CH);
            }
        }

        if (menuselection == 7) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    AISetmenu = 0;
                    menuselection = 2;
                    menuselectionmax = 6;
                    limiterstart++;
                }
            }
        }
        if (presetselector == 1) {
            presetselectorstr[0] = 'C';
            presetselectorstr[1] = 'u';
            presetselectorstr[2] = 's';
            presetselectorstr[3] = 't';
            presetselectorstr[4] = 'o';
            presetselectorstr[5] = 'm';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = ' ';
            presetselectorstr[9] = ' ';
            presetselectorstr[10] = ' ';
            presetselectorstr[11] = ' ';
            presetselectorstr[12] = ' ';

            puppetdifficulty = 15;
            musicboxunwidingvaludemi = 0;
            musicboxunwidingvalue = 2;
            windingframe = 1;
        }
        if (presetselector > 1 && presetselector < 7) {
            presetselectorstr[0] = 'N';
            presetselectorstr[1] = 'i';
            presetselectorstr[2] = 'g';
            presetselectorstr[3] = 'h';
            presetselectorstr[4] = 't';
            presetselectorstr[5] = ' ';
            if (presetselector == 2) {
                presetselectorstr[6] = '2';
                freddydifficulty = 0;
                bonniedifficulty = 0;
                chicadifficulty = 0;
                foxydifficulty = 1;
                puppetdifficulty = 5;
                toyfreddydifficulty = 2;
                toybonniedifficulty = 3;
                toychicadifficulty = 3;
                mangledifficulty = 3;
                BBdifficulty = 3;
                GFdifficulty = 0;
                doescharlevelup = 1;
                musicboxunwidingvaludemi = 0;
                musicboxunwidingvalue = 1;
                musicboxunwidingvaluthird = -2; // OK
                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
            if (presetselector == 3) {
                presetselectorstr[6] = '3';
                freddydifficulty = 0;
                bonniedifficulty = 1;
                chicadifficulty = 1;
                foxydifficulty = 2;
                puppetdifficulty = 8;
                toyfreddydifficulty = 0;
                toybonniedifficulty = 0;
                toychicadifficulty = 0;
                mangledifficulty = 0;
                BBdifficulty = 1;
                GFdifficulty = 0;
                doescharlevelup = 1;
                musicboxunwidingvaludemi = 0;
                musicboxunwidingvalue = 1;
                musicboxunwidingvaluthird = -2;
                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
            if (presetselector == 4) {
                presetselectorstr[6] = '4';
                freddydifficulty = 0;
                bonniedifficulty = 1;
                chicadifficulty = 0;
                foxydifficulty = 7;
                puppetdifficulty = 9;
                toyfreddydifficulty = 0;
                toybonniedifficulty = 0;
                toychicadifficulty = 0;
                mangledifficulty = 5;
                BBdifficulty = 3;
                GFdifficulty = 0;
                doescharlevelup = 1;
                musicboxunwidingvalue = 4;
                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
            if (presetselector == 5) {
                presetselectorstr[6] = '5';
                freddydifficulty = 2;
                bonniedifficulty = 2;
                chicadifficulty = 2;
                foxydifficulty = 5;
                puppetdifficulty = 10;
                toyfreddydifficulty = 5;
                toybonniedifficulty = 2;
                toychicadifficulty = 2;
                mangledifficulty = 1;
                BBdifficulty = 5;
                GFdifficulty = 0;
                doescharlevelup = 1;
                musicboxunwidingvalue = 5;
                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
            if (presetselector == 6) {
                presetselectorstr[6] = '6';
                freddydifficulty = 5;
                bonniedifficulty = 5;
                chicadifficulty = 5;
                foxydifficulty = 10;
                puppetdifficulty = 15;
                toyfreddydifficulty = 0;
                toybonniedifficulty = 0;
                toychicadifficulty = 0;
                mangledifficulty = 3;
                BBdifficulty = 5;
                GFdifficulty = 0;
                doescharlevelup = 1;
                musicboxunwidingvaludemi = 0;
                musicboxunwidingvalue = 2; 
                windingframe = 1;
                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
        } else {
          musicboxunwidingvaludemi = 0;
          musicboxunwidingvalue = 2;
          windingframe = 1;
        }
        if (presetselector == 7) {
            presetselectorstr[0] = '4';
            presetselectorstr[1] = '/';
            presetselectorstr[2] = '2';
            presetselectorstr[3] = '0';
            presetselectorstr[4] = ' ';
            presetselectorstr[5] = ' ';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = ' ';
            presetselectorstr[9] = ' ';
            presetselectorstr[10] = ' ';
            presetselectorstr[11] = ' ';
            presetselectorstr[12] = ' ';
            freddydifficulty = 20;
            bonniedifficulty = 20;
            chicadifficulty = 20;
            foxydifficulty = 20;
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 8) {
            presetselectorstr[0] = 'N';
            presetselectorstr[1] = 'e';
            presetselectorstr[2] = 'w';
            presetselectorstr[3] = ' ';
            presetselectorstr[4] = 'a';
            presetselectorstr[5] = 'n';
            presetselectorstr[6] = 'd';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = 'S';
            presetselectorstr[9] = 'h';
            presetselectorstr[10] = 'i';
            presetselectorstr[11] = 'n';
            presetselectorstr[12] = 'y';
            presetselectorstr[13] = ' ';
            presetselectorstr[14] = ' ';
            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            foxydifficulty = 0;
            toyfreddydifficulty = 10;
            toybonniedifficulty = 10;
            toychicadifficulty = 10;
            mangledifficulty = 10;
            BBdifficulty = 10;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 9) {
            presetselectorstr[0] = 'D';
            presetselectorstr[1] = 'o';
            presetselectorstr[2] = 'u';
            presetselectorstr[3] = 'b';
            presetselectorstr[4] = 'l';
            presetselectorstr[5] = 'e';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = 'T';
            presetselectorstr[8] = 'r';
            presetselectorstr[9] = 'o';
            presetselectorstr[10] = 'u';
            presetselectorstr[11] = 'b';
            presetselectorstr[12] = 'l';
            presetselectorstr[13] = 'e';
            presetselectorstr[14] = ' ';
            presetselectorstr[15] = ' ';
            bonniedifficulty = 20;
            foxydifficulty = 5;
            toybonniedifficulty = 20;

            freddydifficulty = 0;
            chicadifficulty = 0;
            toyfreddydifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 10) {
            presetselectorstr[0] = 'N';
            presetselectorstr[1] = 'i';
            presetselectorstr[2] = 'g';
            presetselectorstr[3] = 'h';
            presetselectorstr[4] = 't';
            presetselectorstr[5] = ' ';
            presetselectorstr[6] = 'o';
            presetselectorstr[7] = 'f';
            presetselectorstr[8] = ' ';
            presetselectorstr[9] = 'm';
            presetselectorstr[10] = 'i';
            presetselectorstr[11] = 's';
            presetselectorstr[12] = 'f';
            presetselectorstr[13] = 'i';
            presetselectorstr[14] = 't';
            presetselectorstr[15] = 's';
            mangledifficulty = 20;
            GFdifficulty = 10;
            BBdifficulty = 20;

            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            foxydifficulty = 0;
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 11) {
            presetselectorstr[0] = 'F';
            presetselectorstr[1] = 'o';
            presetselectorstr[2] = 'x';
            presetselectorstr[3] = 'y';
            presetselectorstr[4] = ' ';
            presetselectorstr[5] = 'F';
            presetselectorstr[6] = 'o';
            presetselectorstr[7] = 'x';
            presetselectorstr[8] = 'y';
            presetselectorstr[9] = ' ';
            presetselectorstr[10] = ' ';
            presetselectorstr[11] = ' ';
            presetselectorstr[12] = ' ';
            presetselectorstr[13] = ' ';
            presetselectorstr[14] = ' ';
            presetselectorstr[15] = ' ';
            presetselectorstr[16] = ' ';
            mangledifficulty = 20;
            foxydifficulty = 20;

            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 12) {
            presetselectorstr[0] = 'L';
            presetselectorstr[1] = 'a';
            presetselectorstr[2] = 'd';
            presetselectorstr[3] = 'i';
            presetselectorstr[4] = 'e';
            presetselectorstr[5] = 's';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = 'N';
            presetselectorstr[8] = 'i';
            presetselectorstr[9] = 'g';
            presetselectorstr[10] = 'h';
            presetselectorstr[11] = 't';
            presetselectorstr[12] = ' ';
            presetselectorstr[13] = ' ';
            presetselectorstr[14] = ' ';
            mangledifficulty = 20;
            chicadifficulty = 20;
            toychicadifficulty = 20;

            freddydifficulty = 0;
            bonniedifficulty = 0;
            foxydifficulty = 0;
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 13) {
            presetselectorstr[0] = 'F';
            presetselectorstr[1] = 'r';
            presetselectorstr[2] = 'e';
            presetselectorstr[3] = 'd';
            presetselectorstr[4] = 'd';
            presetselectorstr[5] = 'y';
            presetselectorstr[6] = '"';
            presetselectorstr[7] = 's';
            presetselectorstr[8] = ' ';
            presetselectorstr[9] = 'C';
            presetselectorstr[10] = 'i';
            presetselectorstr[11] = 'r';
            presetselectorstr[12] = 'c';
            presetselectorstr[13] = 'u';
            presetselectorstr[14] = 's';
            presetselectorstr[15] = ' ';
            presetselectorstr[16] = ' ';
            freddydifficulty = 20;
            toyfreddydifficulty = 20;
            foxydifficulty = 10;
            BBdifficulty = 10;
            GFdifficulty = 10;

            bonniedifficulty = 0;
            chicadifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 14) {
            presetselectorstr[0] = 'C';
            presetselectorstr[1] = 'u';
            presetselectorstr[2] = 'p';
            presetselectorstr[3] = 'c';
            presetselectorstr[4] = 'a';
            presetselectorstr[5] = 'k';
            presetselectorstr[6] = 'e';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = 'C';
            presetselectorstr[9] = 'h';
            presetselectorstr[10] = 'a';
            presetselectorstr[11] = 'l';
            presetselectorstr[12] = 'l';
            presetselectorstr[13] = 'e';
            presetselectorstr[14] = 'n';
            presetselectorstr[15] = 'g';
            presetselectorstr[16] = 'e';
            freddydifficulty = 5;
            bonniedifficulty = 5;
            chicadifficulty = 5;
            foxydifficulty = 5;
            toyfreddydifficulty = 5;
            toybonniedifficulty = 5;
            toychicadifficulty = 5;
            mangledifficulty = 5;
            BBdifficulty = 5;
            GFdifficulty = 5;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 15) {
            presetselectorstr[0] = 'F';
            presetselectorstr[1] = 'a';
            presetselectorstr[2] = 'z';
            presetselectorstr[3] = 'b';
            presetselectorstr[4] = 'e';
            presetselectorstr[5] = 'a';
            presetselectorstr[6] = 'r';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = 'F';
            presetselectorstr[9] = 'e';
            presetselectorstr[10] = 'v';
            presetselectorstr[11] = 'e';
            presetselectorstr[12] = 'r';
            presetselectorstr[13] = ' ';
            presetselectorstr[14] = ' ';
            presetselectorstr[15] = ' ';
            presetselectorstr[16] = ' ';
            freddydifficulty = 10;
            bonniedifficulty = 10;
            chicadifficulty = 10;
            foxydifficulty = 10;
            toyfreddydifficulty = 10;
            toybonniedifficulty = 10;
            toychicadifficulty = 10;
            mangledifficulty = 10;
            BBdifficulty = 10;
            GFdifficulty = 10;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 16) {
            presetselectorstr[0] = 'G';
            presetselectorstr[1] = 'o';
            presetselectorstr[2] = 'l';
            presetselectorstr[3] = 'd';
            presetselectorstr[4] = 'e';
            presetselectorstr[5] = 'n';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = 'F';
            presetselectorstr[8] = 'r';
            presetselectorstr[9] = 'e';
            presetselectorstr[10] = 'd';
            presetselectorstr[11] = 'd';
            presetselectorstr[12] = 'y';
            freddydifficulty = 20;
            bonniedifficulty = 20;
            chicadifficulty = 20;
            foxydifficulty = 20;
            toyfreddydifficulty = 20;
            toybonniedifficulty = 20;
            toychicadifficulty = 20;
            mangledifficulty = 20;
            BBdifficulty = 20;
            GFdifficulty = 20;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
    }
    if (timermenu == 1) {
        advancedmenu = 0;
        if (menuselection == 1) {
            //AM
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    customAM++;
                    if (customAM < 12 && customAM > 6) {customAM = 12;}
                    if (customAM > 12) {customAM = 0;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    customAM--;
                    if (customAM < 12 && customAM > 6) {customAM = 6;}
                    if (customAM < 0) {customAM = 12;}
                    limiterpadleft = 1;
                }
            }
        }
        if (menuselection == 2) {
            //FrameCounterlimit (via the convertion var)
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    convertion++;
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    convertion--;
                    if (convertion < 0) {convertion = 0;}
                    limiterpadleft = 1;
                }
            }
            //For quick change
            if (pad & PADR1) {
                convertion++;
            }
            if (pad & PADL1) {
                convertion--;
                if (convertion < 0) {convertion = 0;}
            }
            //For reset
            if (pad & PADstart) {
                convertion = 60;
            }
            //For 0
            if (pad & PADselect) {
                convertion = 0;
            }
            //For 120
            if (pad & PADstart && pad & PADselect) {
                convertion = 120;
            }
        }
        if (menuselection == 3) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    timermenu = 0;
                    menuselection = 3;
                    menuselectionmax = 6;
                    limiterstart++;
                }
            }
        }
    }
    if (advancedmenu == 1) {
        if (menuselection == 1) { //Old animatronic's frame lock
            if (pad & PADRright) { //Foxy 
                foxylocationframelock++;
            }
            if (pad & PADRleft) { //Foxy 
                foxylocationframelock--;
                if (foxylocationframelock < 1) {foxylocationframelock = 1;}
            }
            if (pad & PADLright) { //Freddy 
                freddylocationframelock++;
            }
            if (pad & PADLleft) { //Freddy 
                freddylocationframelock--;
                if (freddylocationframelock < 1) {freddylocationframelock = 1;}
            }
            if (pad & PADL1) { //Bonnie 
                bonnielocationframelock--;
                if (bonnielocationframelock < 1) {bonnielocationframelock = 1;}
            }
            if (pad & PADL2) { //Bonnie 
                bonnielocationframelock++;
            }
            if (pad & PADR1) { //Chica 
                chicalocationframelock--;
                if (chicalocationframelock < 1) {chicalocationframelock = 1;}
            }
            if (pad & PADR2) { //Chica 
                chicalocationframelock++;
            }
            if (pad & PADstart) {
                freddylocationframe = 300;
                bonnielocationframe = 300;
                chicalocationframe = 300;
                foxylocationframe = 300;
                freddylocationframelock = 300;
                bonnielocationframelock = 300;
                chicalocationframelock = 300;
                foxylocationframelock = 300;
            }
        }
        if (menuselection == 2) {
            if (pad & PADRright) { //Mangle 
                manglelocationframelock++;
            }
            if (pad & PADRleft) { //Foxy 
                manglelocationframelock--;
                if (manglelocationframelock < 1) {manglelocationframelock = 1;}
            }
            if (pad & PADLright) { //Freddy 
                toyfreddylocationframelock++;
            }
            if (pad & PADLleft) { //Freddy 
                toyfreddylocationframelock--;
                if (toyfreddylocationframelock < 1) {toyfreddylocationframelock = 1;}
            }
            if (pad & PADL1) { //Bonnie 
                toybonnielocationframelock--;
                if (toybonnielocationframelock < 1) {toybonnielocationframelock = 1;}
            }
            if (pad & PADL2) { //Bonnie 
                toybonnielocationframelock++;
            }
            if (pad & PADR1) { //Chica 
                toychicalocationframelock--;
                if (toychicalocationframelock < 1) {toychicalocationframelock = 1;}
            }
            if (pad & PADR2) { //Chica 
                toychicalocationframelock++;
            }
            if (pad & PADstart) {
                toyfreddylocationframe = 300;
                toybonnielocationframe = 300;
                toychicalocationframe = 300;
                manglelocationframe = 300;
                toyfreddylocationframelock = 300;
                toybonnielocationframelock = 300;
                toychicalocationframelock = 300;
                manglelocationframelock = 300;
            }
        }
        if (menuselection == 3) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    advancedmenu = 0;
                    menuselection = 4;
                    menuselectionmax = 6;
                    limiterstart++; 
                }
            }
        }
    }
    if (extramenu == 1) {
        if (menuselection == 1) { //Phone guy
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    enablephoneguy++;
                    enablephoneguystr[0] = 'O';
                    enablephoneguystr[1] = 'N';
                    enablephoneguystr[2] = ' ';
                    if (enablephoneguy > 1) {
                        enablephoneguy = 0;
                        enablephoneguystr[0] = 'O';
                        enablephoneguystr[1] = 'F';
                        enablephoneguystr[2] = 'F';
                    }
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 2) { //Unlocks menu
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 0;
                    unlockssubmenu = 1;
                    menuselection = 1;
                    menuselectionmax = 4;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 3) { //Informations on the game
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 0;
                    infoscreen = 1;
                    menuselection = 1;
                    menuselectionmax = 1;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 4) {//Two players mode
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    twoplayermode++;
                    if (twoplayermode > 1) {twoplayermode = 0;}
                    
                    if (twoplayermode == 0) {
                        twoplayermodestr[1] = 'F';
                        twoplayermodestr[2] = 'F';
                    } else {
                        twoplayermodestr[1] = 'N';
                        twoplayermodestr[2] = ' ';
                    }
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 5) { //Return
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                    extramenu = 0;
                    menuselection = 3;
                    limiterstart++;
                    if (activatedmenudebug == 0) {menuselectionmax = 4;}
                    else {menuselectionmax = 5;}
                }
            }
        }
        if (menuselection == 6) { //Toggle Weird night
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                  weirdnight = 1;
                  oldnight = night;
                  night = 725255;
                  onetime++;
                  limiterstart++;
                  menu = 1;
                }
            }
        }
        if (menuselection == 7) { //Toggle debug mode
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                  debugging = 1;
                }
            }
        }
    }
    if (infoscreen == 1) {
        if (menuselection == 1) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 1;
                    infoscreen = 0;
                    menuselection = 1;
                    if (activatedmenudebug == 0) {
                        menuselectionmax = 5;
                    }
                    if (activatedmenudebug == 1) {
                        menuselectionmax = 5;
                    }
                    limiterstart = 1;
                }
            }
        }
    }
    if (unlockssubmenu == 1) {
        if (menuselection == 1) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    unlimitedpower++;
                    unlimitedpowerstr[0] = 'O';
                    unlimitedpowerstr[1] = 'N';
                    unlimitedpowerstr[2] = ' ';
                    if (unlimitedpower > 1) {
                        unlimitedpower = 0;
                        unlimitedpowerstr[0] = 'O';
                        unlimitedpowerstr[1] = 'F';
                        unlimitedpowerstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 2) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    fastnights++;
                    fastnightsstr[0] = 'O';
                    fastnightsstr[1] = 'N';
                    fastnightsstr[2] = ' ';
                    if (fastnights > 1) {
                        fastnights = 0;
                        fastnightsstr[0] = 'O';
                        fastnightsstr[1] = 'F';
                        fastnightsstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 3) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    radar++;
                    radarstr[0] = 'O';
                    radarstr[1] = 'N';
                    radarstr[2] = ' ';
                    if (radar > 1) {
                        radar = 0;
                        radarstr[0] = 'O';
                        radarstr[1] = 'F';
                        radarstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 4) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 1;
                    unlockssubmenu = 0;
                    menuselection = 1;
                    if (activatedmenudebug == 0) {
                        menuselectionmax = 5;
                    }
                    if (activatedmenudebug == 1) {
                        menuselectionmax = 6;
                    }
                    limiterstart = 1;
                }
            }
        }
    }
}
void menuPrint(void) {
    if (maincustomnightmenu == 0 && extramenu == 0 && infoscreen == 0 && unlockssubmenu == 0 && AISetmenu == 0 && timermenu == 0 && advancedmenu == 0) {
        FntPrint("   Five\n\n   Nights\n\n   at\n\n   Freddy's\n\n   2 \n\n\n");  // print time

        if (menuselection == 1) {FntPrint(">> New Game\n\n");}
        else {FntPrint("   New Game\n\n");}

        if (activatedmenudebug == 0) {
            if (menuselection == 2) {FntPrint(">> Continue Night %d\n\n", night);}
            else {FntPrint("   Continue Night %d\n\n", night);}
        } else {
            if (menuselection == 2) {FntPrint(">> Continue Night %d (AI level forceset)\n\n", night);}
            else {FntPrint("   Continue Night %d\n\n", night);}
        }

        if (menuselection == 3) {FntPrint(">> Extra menu \n\n");}
        else {FntPrint("   Extra menu \n\n");}

        if (menuselection == 4) {FntPrint(">> Custom Night \n\n");}
        else {FntPrint("   Custom Night \n\n");}

        if (activatedmenudebug == 1) {
            if (menuselection == 5) {FntPrint(">> Debugprint %d\n\n", printnumber);}
            else {FntPrint("   Debugprint \n\n");}
        }
    }
    if (maincustomnightmenu == 1) {
        FntPrint("   Custom\n\n   Night\n\n\n");  // print time

        FntPrint("   Welcome! What do you want to modify?\n\n\n\n");

        if (menuselection == 1) {FntPrint(">> Night : %d\n\n", night);}
        else {FntPrint("   Night : %d\n\n", night);}
        if (menuselection == 2) {FntPrint(">> Set AI levels\n\n");}
        else {FntPrint("   Set AI levels\n\n");}
        if (menuselection == 3) {FntPrint(">> Set Timer, ect.\n\n");}
        else {FntPrint("   Set Timer, ect.\n\n");}
        if (menuselection == 4) {FntPrint(">> Advanced settings\n\n");}
        else {FntPrint("   Advanced settings\n\n");}
        if (menuselection == 5) {FntPrint(">> Launch custom night\n\n");}
        else {FntPrint("   Launch custom night\n\n");}
        if (menuselection == 6) {FntPrint(">> Return to main menu\n\n");}
        else {FntPrint("   Return to main menu\n\n");}
    }
    if (AISetmenu == 1) {
        FntPrint("   Custom\n\n   Night\n\n\n");  // print time
        FntPrint("   Set Ai Level Menu\n\n\n");
        if (animatronicategorie == 1) {
            if (menuselection == 1) {FntPrint(">> Freddy : %d\n\n", freddydifficulty );}
            else {FntPrint("   Freddy : %d\n\n", freddydifficulty );}
            if (menuselection == 2) {FntPrint(">> Bonnie : %d\n\n", bonniedifficulty );}
            else {FntPrint("   Bonnie : %d\n\n", bonniedifficulty );}
            if (menuselection == 3) {FntPrint(">> Chica : %d\n\n", chicadifficulty );}
            else {FntPrint("   Chica : %d\n\n", chicadifficulty );}
            if (menuselection == 4) {FntPrint(">> Foxy : %d\n\n", foxydifficulty );}
            else {FntPrint("   Foxy : %d\n\n", foxydifficulty );}
        }
        if (animatronicategorie == 2) {
            if (menuselection == 1) {FntPrint(">> Toy Freddy : %d\n\n", toyfreddydifficulty );}
            else {FntPrint("   Toy Freddy : %d\n\n", toyfreddydifficulty );}
            if (menuselection == 2) {FntPrint(">> Toy Bonnie : %d\n\n", toybonniedifficulty );}
            else {FntPrint("   Toy Bonnie : %d\n\n", toybonniedifficulty );}
            if (menuselection == 3) {FntPrint(">> Toy Chica : %d\n\n", toychicadifficulty );}
            else {FntPrint("   Toy Chica : %d\n\n", toychicadifficulty );}
            if (menuselection == 4) {FntPrint(">> Mangle : %d\n\n", mangledifficulty );}
            else {FntPrint("   Mangle : %d\n\n", mangledifficulty );}
        }
        if (animatronicategorie == 3) {
            if (menuselection == 1) {FntPrint(">> Ballon Boy : %d\n\n", BBdifficulty );}
            else {FntPrint("   Ballon Boy : %d\n\n", BBdifficulty );}
            if (menuselection == 2) {FntPrint(">> Golden Freddy : %d\n\n", GFdifficulty );}
            else {FntPrint("   Golden Freddy : %d\n\n", GFdifficulty );}
            if (menuselection == 3) {FntPrint(">> Character leveling ? : %s \n\n", doescharlevelupstr );}
            else {FntPrint("   Character leveling ? : %s \n\n", doescharlevelupstr );}
            if (menuselection == 4) {FntPrint(">> \n\n");}
            else {FntPrint("   \n\n" );}
        }
        if (menuselection == 5) {FntPrint(">> Categorie %d\n\n",animatronicategorie);}
        else {FntPrint("   Categorie %d \n\n", animatronicategorie);}
        if (menuselection == 6) {FntPrint(">> Preset : %s\n\n", presetselectorstr);}
        else {FntPrint("   Preset : %s\n\n",presetselectorstr);}
        if (menuselection == 7) {FntPrint(">> Return to Custom night menu\n\n");}
        else {FntPrint("   Return to Custom night menu\n\n");}
    }
    if (timermenu == 1) {
        FntPrint("   Custom\n\n   Night\n\n\n");  // print time
        FntPrint("   Set timer, ect Menu\n\n\n");

        if (menuselection == 1) {FntPrint(">> Set beginning AM %d\n\n", customAM );}
        else {FntPrint("   Set beginning AM %d\n\n", customAM );}
        if (menuselection == 2) {FntPrint(">> 1 Hour = %d seconds in game\n\n", convertion );}
        else {FntPrint("   1 Hour = %d seconds in game\n\n", convertion );}
        if (menuselection == 3) {FntPrint(">> Return to Custom night menu\n\n");}
        else {FntPrint("   Return to Custom night menu\n\n");}
        //Maybe put end AM
    }
    if (advancedmenu == 1) {
        FntPrint("   Custom\n\n   Night\n\n\n");  // print time
        FntPrint("   Advanced Settings Menu\n\n\n");

        if (menuselection == 1) {FntPrint(">> Cooldown FBCFo : %d %d %d %d\n\n", freddylocationframelock, bonnielocationframelock, chicalocationframelock, foxylocationframelock );}
        else {FntPrint("   Cooldown of old animatronics : ...\n\n" );}
        if (menuselection == 2) {FntPrint(">> Cooldown FBCM : %d %d %d %d\n\n", toyfreddylocationframelock, toybonnielocationframelock, toychicalocationframelock, manglelocationframelock );}
        else {FntPrint("   Cooldown of toy animatronics : ...\n\n" );}
        if (menuselection == 3) {FntPrint(">> Return to Custom night menu\n\n");}
        else {FntPrint("   Return to Custom night menu\n\n");}
    }
    if (extramenu == 1) {
        FntPrint("   Extra\n\n   Menu\n\n\n");  // print time

        if (menuselection == 1) {FntPrint(">> Enable phone guy ? %s\n\n", enablephoneguystr);}
        else {FntPrint("   Enable phone guy ? %s\n\n", enablephoneguystr);}

        if (menuselection == 2) {FntPrint(">> Unlocks menu\n\n");}
        else {FntPrint("   Unlocks menu\n\n");}

        if (menuselection == 3) {FntPrint(">> Info screen\n\n");}
        else {FntPrint("   Info screen\n\n");}

        if (menuselection == 4) {FntPrint(">> Two Player Mode : %s\n\n", twoplayermodestr);}
        else {FntPrint("   Two Player Mode : %s\n\n", twoplayermodestr);}

        if (menuselection == 5) {FntPrint(">> Return to main menu\n\n");}
        else {FntPrint("   Return to main menu\n\n");}

        if (activatedmenudebug == 1) {
            if (menuselection == 6) {FntPrint(">> Toggle weird night\n\n");}
            else {FntPrint("   Toggle weird night\n\n");}

            if (menuselection == 7) {FntPrint(">> Toggle debugging\n\n");}
            else {FntPrint("   Toggle debugging\n\n");}
        }
    }
    if (infoscreen == 1) {
        FntPrint("           Information Screen\n\n");

        FntPrint("   Five Night at Freddy's 2 has been \n   released by Scott Cawton on 2014,\nand has been ported on the PS1 by Soeiz.\n         Again, Thank you, Scott, \n For feeding our imagination with this\n                  world.\n\n");

        FntPrint(">> Back                      V1.0\n"); //Don't even need to do condition, there's only one
    }
    if (unlockssubmenu == 1) {
        FntPrint("   Unlocks\n\n   Menu\n\n\n");  // print time

        if (menuselection == 1) {FntPrint(">> Unlimited Power : %s\n\n", unlimitedpowerstr);}
        else {FntPrint("   Unlimited Power : %s\n\n", unlimitedpowerstr);}

        if (menuselection == 2) {FntPrint(">> Fast Nights : %s\n\n", fastnightsstr);}
        else {FntPrint("   Fast Nights : %s\n\n", fastnightsstr);}

        if (menuselection == 3) {FntPrint(">> Radar Map : %s\n\n", radarstr);}
        else {FntPrint("   Radar Map : %s\n\n", radarstr);}

        if (menuselection == 4) {FntPrint(">> Back \n\n");}
        else {FntPrint("   Back \n\n");}
    }
}
void gameoverprint(void) {
    FntPrint("\n\n      Congrats! You just... Died.\nGo on and press start to try your luck                 again !\n");
    if (activatedmenudebug == 1) {
        FntPrint("             Killer : %d",deadfrom);
    }
}
void controllerinput(void) {
  if (!(night == 725255 && phoneguytalking < 960)) {
    if (camera == 0 && ismaskon == 0) {
        if(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1) { //Up
            if (limiterbop == 1) {return;}
            if (MovVectorofficemiddle.vx > 50) {
                SpuSetKey(SPU_ON, SPU_05CH);
                limiterbop = 1;
            }
        }
        if(!(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1)) {limiterbop = 0;}

        if(!(pad & PADRdown || pad >> 16 & PADRdown && twoplayermode == 1)) {limiter3 = 0;}

        if(pad & PADRright || pad >> 16 & PADRright && twoplayermode == 1) { //Circle
            if (limiter2 == 1) {return;}
            LightFunc();
        }
        if(!(pad & PADRright || pad >> 16 & PADRright && twoplayermode == 1)) {limiter2 = 0;}

        if (pad & PADRup || pad >> 16 & PADRup && twoplayermode == 1) { //Triangle
            if (limiterhall == 1) {return;}
            LightFuncHall();
        }
        if(!(pad & PADRup || pad >> 16 & PADRup && twoplayermode == 1)) {limiterhall = 0;}

    }
        if (camera == 0) {     
            if (pad & PADL1 || pad >> 16 & PADL1 && twoplayermode == 1) {
                if (masklimiter == 1) {return;}
                if (checkframes == 0 || ismaskon == 0) {
                    MaskFunc();
                }
            }
            if(!(pad & PADL1 || pad >> 16 & PADL1 && twoplayermode == 1)) {masklimiter = 0;}
        }

        if (ismaskon == 0) {
            if(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1) { //R1
                if (camlimiter == 1) {return;}
                  CameraFunc(0);
            }
            if(!(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1)) {camlimiter = 0;}
        }
  }
    //Left
    if(pad & PADLleft || pad >> 16 & PADLleft && twoplayermode == 1) {sideFunc(0);}
    //Right
    if(pad & PADLright || pad >> 16 & PADLright && twoplayermode == 1) {sideFunc(1);}    
}
void animatronicFunc(int init) {
    if (init == 1) {
        if (night == 1 && FrameCounter == 0) { //Setting difficulties
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            foxydifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 1;
            windingframe = 96857441;
            checklifelimit = 100; 
            flashlightbattery = 7200; //6200 is 120 in seconds
        }
        if (night == 2 && FrameCounter == 0) { 
            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 5;
            toybonniedifficulty = 3;
            toychicadifficulty = 3;
            foxydifficulty = 1;
            mangledifficulty = 3;
            toyfreddydifficulty = 2;
            BBdifficulty = 3;
            musicboxunwidingvalue = 2;
            musicboxunwidingvaludemi = 1;
            musicboxunwidingvaluthird = -2; // OK
            windingframe = 2;
            checklifelimit = 80; 
            flashlightbattery = 6000; //6000 is 100 in seconds
        }
        if (night == 3 && FrameCounter == 0) { 
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            freddydifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 8;
            bonniedifficulty = 1;
            BBdifficulty = 1;
            chicadifficulty = 1;
            foxydifficulty = 2;
            musicboxunwidingvaludemi = 0;
            musicboxunwidingvalue = 2;
            musicboxunwidingvaluthird = -2; // OK
            windingframe = 1;
            checklifelimit = 60; 
            flashlightbattery = 4800; //4800 is 80 in seconds
        }
        if (night == 4 && FrameCounter == 0) { 
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            freddydifficulty = 0;
            chicadifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 9;
            bonniedifficulty = 1;
            foxydifficulty = 7;
            BBdifficulty = 3;
            mangledifficulty = 5;
            musicboxunwidingvaludemi = 1;
            musicboxunwidingvalue = 2;
            musicboxunwidingvaluthird = 0; //Curr 26.54 / 25
            windingframe = 1;
            checklifelimit = 55; 
            flashlightbattery = 4500; //4500 is 75 in seconds
        }
        if (night == 5 && FrameCounter == 0) { 
            GFdifficulty = 0;
            puppetdifficulty = 10;
            freddydifficulty = 2;
            bonniedifficulty = 2;
            chicadifficulty = 2;
            foxydifficulty = 5;
            BBdifficulty = 5;
            toyfreddydifficulty = 5;
            toybonniedifficulty = 2;
            toychicadifficulty = 2;
            mangledifficulty = 1;
            musicboxunwidingvaludemi = 1;
            musicboxunwidingvalue = 3;
            musicboxunwidingvaluthird = 0; //Cur 19.13 / 20
            windingframe = 1;
            checklifelimit = 50; 
            flashlightbattery = 3000; //3000 is 50 in seconds
        }
        if (night == 6 && FrameCounter == 0) { 
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 15;
            freddydifficulty = 5;
            bonniedifficulty = 5;
            chicadifficulty = 5;
            foxydifficulty = 10;
            mangledifficulty = 3;
            BBdifficulty = 5;
            musicboxunwidingvaludemi = 0;
            musicboxunwidingvalue = 4; //Cur ~16.55 OK
            windingframe = 1;
            checklifelimit = 50; 
            flashlightbattery = 3000; //3000 is 50 in seconds
        }
    } else {
    if (debugging == 1) {
      if (FrameCounter == 0) {
        if (AM == 12) {
          toychicalocation = 2;
        }
        if (AM == 1) {
          toychicalocation--;
          freddylocation = 3;
        }
        if (AM == 2) {
          freddylocation--;
          bonnielocation = 2;
        }
        if (AM == 3) {
          bonnielocation--;
          foxylocation = 1;
        }
        if (AM == 4) {
          foxylocation--;
          toyfreddylocation = 2;
        }
      }
    }
    if (doescharlevelup == 1){
        if (FrameCounter == 0) {
          if (AM == 1) {
            if (night == 2) {
              toybonniedifficulty = toybonniedifficulty + 3;
              toychicadifficulty = toychicadifficulty + 3;
              toyfreddydifficulty = toyfreddydifficulty + 2;
              mangledifficulty = mangledifficulty + 3;
              BBdifficulty = BBdifficulty + 3;
              foxydifficulty = foxydifficulty + 1;
            }
            if (night == 3) {
              freddydifficulty = freddydifficulty + 2;
              bonniedifficulty = bonniedifficulty + 2;
              chicadifficulty++;
              foxydifficulty++;
              BBdifficulty++;
              toybonniedifficulty++;
              toychicadifficulty++;
            }
            if (night == 5) {
              freddydifficulty = freddydifficulty + 3;
              bonniedifficulty = bonniedifficulty + 3;
              chicadifficulty = chicadifficulty + 3;
              foxydifficulty = foxydifficulty + 2;
              toyfreddydifficulty = toyfreddydifficulty - 4;
              mangledifficulty = mangledifficulty + 9;
              toybonniedifficulty++;
            }
          }
          if (AM == 2) {
            if  (night == 1) {
              toybonniedifficulty = toybonniedifficulty + 2;
              toychicadifficulty = toychicadifficulty + 2;
              musicboxunwidingvalue = 1;
              musicboxunwidingvaludemi = 1;
              musicboxunwidingvaluthird = -2;
              windingframe = 2;
            }
            if (night == 4) {
              freddydifficulty = freddydifficulty + 3;
              bonniedifficulty = bonniedifficulty + 3;
              chicadifficulty = chicadifficulty + 4;
              toybonniedifficulty++;
            }
            if (night == 6) {
              toybonniedifficulty = toybonniedifficulty + 5;
              GFdifficulty = GFdifficulty + 3;
              foxydifficulty = foxydifficulty + 5;
              toyfreddydifficulty = toyfreddydifficulty + 5;
              toychicadifficulty = toychicadifficulty + 5;
              mangledifficulty = mangledifficulty + 7;
              BBdifficulty = BBdifficulty + 4;
              freddydifficulty = freddydifficulty + 5;
              bonniedifficulty = bonniedifficulty + 5;
              chicadifficulty = chicadifficulty + 5;
            }
          }
          if (AM == 3) {
            if (night == 1) {
              toybonniedifficulty++;
              toyfreddydifficulty = toyfreddydifficulty + 2;
            }
          }
        }
    }
    if (isalreadydead == 1) {
        lastsecondsframes--;
        if (camera == 0) {lastsecondsframes = 0;}
        if (lastsecondsframes == 1001) {
            //Sound moaning ? 
        }
        if (lastsecondsframes == 480) {
            //Second moaning ?
        }
        if (lastsecondsframes == 0) {
            dead = 1;
        }
    }
    if (isalreadydeadlow == 1) { //Usually for GF only
        if (camera == 0) {
            dead = 1;
            deadfrom = 9;
        }
    }
    if (nightwon == 0) {
      AImoving();
    }
  }
}
void AImoving(void) {
    if (animatronicscamera[0] == 0 && freddylocation < 4) {freddylocationframe--;}
    if (animatronicscamera[1] == 0 && bonnielocation < 5) {bonnielocationframe--;}
    if (animatronicscamera[2] == 0 && chicalocation < 5) {chicalocationframe--;}
    foxylocationframe--;

    if (toychicalocation == 2) {animatronicshallway[5] = 1;} else {animatronicshallway[5] = 0;}
    if (toyfreddylocation == 2 || toyfreddylocation == 3) {animatronicshallway[4] = 1;} else {animatronicshallway[4] = 0;}
    if (bonnielocation == 2) {animatronicshallway[1] = 1;} else {animatronicshallway[1] = 0;}
    if (freddylocation == 3) {animatronicshallway[0] = 1;} else {animatronicshallway[0] = 0;}
    if (foxylocation == 1) {animatronicshallway[3] = 1;} else {animatronicshallway[3] = 0;}
    if (manglelocation == 4) {animatronicshallway[6] = 1;} else {animatronicshallway[6] = 0;}

    if (GFactivatedhallway == 1) {animatronicshallway[7] = 1;} else {animatronicshallway[7] = 0;}

    for (int i = 0; i < 7; i++){ if (animatronicshallway[i] == 1){ issomeonehall = 1; break;} else {issomeonehall = 0;}}

    BBlocationframe--;
    GFlocationframehallway--;
    GFlocationframe--; 

    toyfreddylocationframe--; 

    if (!(toybonnielocation == 5 && ismaskon == 1)) {
        toybonnielocationframe--; 
    }

    toychicalocationframe--; 

    if (manglelocation < 8) {
      manglelocationframe--; 
    } else {
      mangleattack--;
      if (mangleattack <= 0) {
        if (camera == 1) {
            isalreadydead = 1;
        }
        deadfrom = 8;
      }
    }

    if (toybonnielocation == 5) {toybonnieHere = 1;} else {toybonnieHere = 0;}
    if (toychicalocation == 5) {toychicaHere = 1;} else {toychicaHere = 0;}
    if (manglelocation == 7) {mangleHere = 1;} else {mangleHere = 0;}
    if (BBlocation == 5) {BBHere = 1;} else {BBHere = 0;}

    if (camera == 0 || camera == 1 && onesecondvar == 0){
        if (toybonnielocation == 6) {
            for (int i = 0; i < 5; i++){ 
                if (officequeue[i] != 6) {
                    if (officequeue[i] == 0){ 
                        officequeue[i] = 6; 
                        break;
                    }
                }
            }
          toybonnielocation++;
        }
        if (bonnielocation == 5) {
            for (int i = 0; i < 5; i++){ 
                if (officequeue[i] != 2) {
                    if (officequeue[i] == 0){ 
                        officequeue[i] = 2; 
                        officequeuetimer = officequeuetimer + 1;
                        break;
                    }
                }
            }
          bonnielocation++;
        }
        if (freddylocation == 4) {
            for (int i = 0; i < 5; i++){ 
                if (officequeue[i] != 1) {
                    if (officequeue[i] == 0){ 
                        officequeue[i] = 1; 
                        officequeuetimer = officequeuetimer + 1;
                        break;
                    }
                }
            }
          freddylocation++;
        }
        if (chicalocation > 4) {
            for (int i = 0; i < 5; i++) { 
                if (officequeue[i] != 3) {
                    if (officequeue[i] == 0) { 
                        officequeue[i] = 3; 
                        officequeuetimer = officequeuetimer + 1;
                        break;
                    }
                } else {break;}
            }
            chicalocation++;
        }
        if (toyfreddylocation == 4) {
            for (int i = 0; i < 5; i++){ 
                if (officequeue[i] != 5) {
                    if (officequeue[i] == 0){ 
                        officequeue[i] = 5; 
                        officequeuetimer = officequeuetimer + 1;
                        break;
                    }
                }
            }
          toyfreddylocation++;
        }        
    }

    //IDK Where to put the music box's AI Here, since it is not moving ?? 🤓 But technicaly it is, because hum you use the wrong combination of words, it is not moving but functionning !!§

    //if (musicboxframes == 0) {musicboxframes = 1;} else {musicboxframes--;} //Kinda dumb, I'll let it here

    if (musicboxtimer > 0) {
      if (windingframe == 0) {
        musicboxtimer = musicboxtimer - musicboxunwidingvalue;
        if (musicboxunwidingvaluthird == 1) {
          musicboxtimer = musicboxtimer - musicboxunwidingvaluthird;
          musicboxunwidingvaluthird = -1;
        }
        if (musicboxunwidingvaluthird == 0) {
          musicboxunwidingvaluthird = 1;
        }
        if (musicboxunwidingvaluthird == -1) {
          musicboxunwidingvaluthird = 0;
        }

        if (musicboxunwidingvaludemi == 0) {
          musicboxunwidingvaludemi = 1;
        } else {
            musicboxunwidingvaludemi = 0;
            musicboxtimer = musicboxtimer - musicboxunwidingvaludemi;
        }
      }
    } else {
      ismusicboxatzero = 1;
    }
    if (dangerlevel == 1) {LoadTexture(_binary_tim_danger1_tim_start, &danger);}
    if (dangerlevel == 2) {LoadTexture(_binary_tim_danger2_tim_start, &danger);}
    if (camera == 1) {
      if (musicboxtimer < 0) {setRGB0(polytimer,0,0,0);} else {setRGB0(polytimer,128,128,128);}

      if (musicboxtimer < 190) {
        LoadTexture(_binary_tim_timer_timer0_tim_start, &timermusicbox);
        dangerlevel = 2;
    }
      if (musicboxtimer > 190 && musicboxtimer < 280) {
        LoadTexture(_binary_tim_timer_timer1_tim_start, &timermusicbox);
        dangerlevel = 2;
    }
      if (musicboxtimer > 280 && musicboxtimer < 370) {
        LoadTexture(_binary_tim_timer_timer2_tim_start, &timermusicbox);
        dangerlevel = 1;
    }
      if (musicboxtimer > 370 && musicboxtimer < 460) {
        LoadTexture(_binary_tim_timer_timer3_tim_start, &timermusicbox);
        dangerlevel = 1;
    }
      if (musicboxtimer > 460 && musicboxtimer < 550) {
        LoadTexture(_binary_tim_timer_timer4_tim_start, &timermusicbox);
        dangerlevel = 0;
    }
      if (musicboxtimer > 550 && musicboxtimer < 640) {LoadTexture(_binary_tim_timer_timer5_tim_start, &timermusicbox);}
      if (musicboxtimer > 640 && musicboxtimer < 730) {LoadTexture(_binary_tim_timer_timer6_tim_start, &timermusicbox);}
      if (musicboxtimer > 730 && musicboxtimer < 820) {LoadTexture(_binary_tim_timer_timer7_tim_start, &timermusicbox);}
      if (musicboxtimer > 820 && musicboxtimer < 910) {LoadTexture(_binary_tim_timer_timer8_tim_start, &timermusicbox);}
      if (musicboxtimer > 910 && musicboxtimer < 1000) {LoadTexture(_binary_tim_timer_timer9_tim_start, &timermusicbox);}
      if (musicboxtimer > 1000 && musicboxtimer < 1090) {LoadTexture(_binary_tim_timer_timer10_tim_start, &timermusicbox);}
      if (musicboxtimer > 1090 && musicboxtimer < 1180) {LoadTexture(_binary_tim_timer_timer11_tim_start, &timermusicbox);}
      if (musicboxtimer > 1180 && musicboxtimer < 1270) {LoadTexture(_binary_tim_timer_timer12_tim_start, &timermusicbox);}
      if (musicboxtimer > 1270 && musicboxtimer < 1360) {LoadTexture(_binary_tim_timer_timer13_tim_start, &timermusicbox);}
      if (musicboxtimer > 1360 && musicboxtimer < 1450) {LoadTexture(_binary_tim_timer_timer14_tim_start, &timermusicbox);}
      if (musicboxtimer > 1450 && musicboxtimer < 1540) {LoadTexture(_binary_tim_timer_timer15_tim_start, &timermusicbox);}
      if (musicboxtimer > 1540 && musicboxtimer < 1630) {LoadTexture(_binary_tim_timer_timer16_tim_start, &timermusicbox);}
      if (musicboxtimer > 1630 && musicboxtimer < 1720) {LoadTexture(_binary_tim_timer_timer17_tim_start, &timermusicbox);}
      if (musicboxtimer > 1720 && musicboxtimer < 1810) {LoadTexture(_binary_tim_timer_timer18_tim_start, &timermusicbox);}
      if (musicboxtimer > 1810 && musicboxtimer < 1900) {LoadTexture(_binary_tim_timer_timer19_tim_start, &timermusicbox);}
      if (musicboxtimer > 1900 && musicboxtimer < 1990) {LoadTexture(_binary_tim_timer_timer20_tim_start, &timermusicbox);}
    } else {
      if (fanframes == 0) {LoadTexture(_binary_tim_office_fan1_tim_start, &tableFAN);}
      if (fanframes == 1) {LoadTexture(_binary_tim_office_fan2_tim_start, &tableFAN);}
      if (fanframes == 2) {LoadTexture(_binary_tim_office_fan3_tim_start, &tableFAN);}
      if (fanframes == 3) {LoadTexture(_binary_tim_office_fan4_tim_start, &tableFAN);}
    }

      if (musicboxtimer < 180) {
        dangerlevel = 2;
    }
      if (musicboxtimer > 180 && musicboxtimer < 360) {
        dangerlevel = 1;
    }
      if (musicboxtimer > 360) {
        dangerlevel = 0;
    }

    if (windingframessound != 0) {
      windingframessound--;
    }

    if (windingframe != 0) {
      windingframe--;
    } else {
      if (night == 2) {
          windingframe = 2;
      } else {
        windingframe = 1;
      }
    }

    if (toychicalocation == 5) {
        if (onesecondvar == 0) {
            Ran(10); 
            if (RAN == 1) {
                if (ismaskon == 1) {
                    toychicalocation = 1;
                    ventbanging = 1; 
                } else {
                    isalreadydead = 5;
                    deadfrom = 7;
                }
            }
        }
        if (ismaskon == 1) {
          toychicafoolness++;
          if (toychicafoolness > 300) {
              toychicalocation = 1;
              ventbanging = 1; 
              toychicafoolness = 0;
          }
        }
    }
    if (manglelocation == 7) {
        if (onesecondvar == 0) {
            Ran(10); 
            if (RAN == 1) {
                if (ismaskon == 1) {
                    manglelocation = 1;
                    ventbanging = 1; 
                } else {
                    manglelocation++;
                    Ran(6000);
                    mangleattack = 300 + RAN; //From 30 seconds to 2 minutes
                    LoadTexture(_binary_tim_office_manglehanging_tim_start, &manglehanging);
                }
            }
        }
        if (ismaskon == 1) {
          manglefoolness++;
          if (manglefoolness > 300) {
              manglelocation = 1;
              ventbanging = 1; 
              manglefoolness = 0;
          }
        }
    }

    if (ismusicboxatzero == 1 && night != 725255) {
      puppetlocationframe--;
      if (puppetlocationframe == 0) {
        Ran(20);
        if (puppetdifficulty > RAN) {
          puppetlocation++;
        }
        puppetlocationframe = 60;
        if (puppetlocation == 5) {
          dead = 1;
          deadfrom = 10;
        }
      }
    }

    if (BBlocationframe < 0 && BBdifficulty != 0) {
        Ran(20);
        if (BBdifficulty > RAN) { 
            if (BBlocation < 5) {
                BBlocation++;
                if (BBlocation == 4) {ventbanging = 1;}
                BBlolonce = 1;
            }
        }
        BBlocationframe = BBlocationframelock;
    }

    if (BBlocation == 5) {
        if (onesecondvar == 0) {
            Ran(10); 
            if (RAN == 1) {
                if (ismaskon == 1) {
                    BBlocation = 1;
                    ventbanging = 1; 
                } else {
                    BBlocation++;
                }
            }
        }
        if (ismaskon == 1) {
          BBfoolness++;
          if (BBfoolness > 300) {
              BBlocation = 1;
              ventbanging = 1; 
              BBfoolness = 0;
          }
        }
    }

    if (freddylocationframe < 0 && freddydifficulty != 0) {
        Ran(20); //Roll time !!!!!!!
        if (freddydifficulty > RAN) { //If freddy's AI level is superior to the current RAN, ...
            if (freddylocation < 4) {
                if (freddylocation == 2 && lighthall == 1) {
                  LightFuncHall();
                }
                if (!(freddylocation == 3 && lighthall == 1)) {freddylocation++;}
              
            }
        }
        freddylocationframe = freddylocationframelock;
    }

    if (bonnielocationframe < 0 && bonniedifficulty != 0) {
        Ran(20);
        if (bonniedifficulty > RAN) {
            if (bonnielocation < 5) {
                if (bonnielocation == 1 && lighthall == 1) {
                  LightFuncHall();
                }
                if (!(bonnielocation == 2 && lighthall == 1)) {bonnielocation++;}
            }
            if (bonnielocation == 4) {ventbanging = 1;}
        }   
        bonnielocationframe = bonnielocationframelock;
    }

    if (chicalocationframe < 0 && chicadifficulty != 0) {
        Ran(20);
        if (chicadifficulty > RAN) {
            if (chicalocation < 5) {
                chicalocation++;  
            }
            if (chicalocation == 3) {ventbanging = 1;}
        }   
        chicalocationframe = chicalocationframelock;
    }
    
    if (toyfreddylocationframe < 0 && toyfreddydifficulty != 0) {
      if (toyfreddylocation < 5) {
        Ran(20);
        if (toyfreddydifficulty > RAN) {
                if (toyfreddylocation == 1 && lighthall == 1) {
                  LightFuncHall();
                }
          if (!(toyfreddylocation == 2 && lighthall == 1 || toyfreddylocation == 3 && lighthall == 1)) {toyfreddylocation++;}
        }
        toyfreddylocationframe = toyfreddylocationframelock;
      }
    }

    if (toybonnielocationframe < 0) {
          if (toybonniedifficulty != 0) {
            Ran(20);
            if (toybonniedifficulty > RAN && !(toybonnielocation == 5 && ismaskon == 1)) {
                if (toybonnielocation < 5) {
                  toybonnielocation++;
                  if (toybonnielocation == 6 && ismaskon == 0) {
                    dead = 1;
                    deadfrom = 6;
                  }
                  if (toybonnielocation == 5 && light2 == 1) {
                    sideFunc(1);
                    LightFunc();
                  }
                  if (toybonnielocation == 4) {ventbanging = 1;}
                }
            }
          }
        if (!(toybonnielocation == 5 && ismaskon == 1)) {toybonnielocationframe = toybonnielocationframelock;}
    }

    if (toybonnielocation == 5 && ismaskon == 1) {
        toybonnieframevent--;
        
        if (toybonnieframevent == 0) {
            toybran = Ran(100);
            if (officequeuetimer == 0) {
                if (officequeue[0] == 0) {
                  toybonnieframevent = 30;
                  if (toybran < 50) {toybonnielocation++; toybran = 999;}
                } else {
                  toybonnieframevent = 60;
                  if (toybran < 33) {toybonnielocation++; toybran = 999;}
                }
            }
        }
    }

    if (toychicalocationframe < 0 && toychicadifficulty != 0) {
        Ran(20);
        if (toychicadifficulty > RAN) {
            if (toychicalocation < 5) {
                if (toychicalocation == 1 && lighthall == 1) {
                  LightFuncHall();
                }
              if (!(toychicalocation == 2 && lighthall == 1)) {toychicalocation++;}
                if (toychicalocation == 5 && light1 == 1) {
                    sideFunc(0);
                    LightFunc();
                }
                if (toychicalocation == 4) {ventbanging = 1;}

            }
        }
        toychicalocationframe = toychicalocationframelock;
    }
    if (manglelocationframe < 0 && mangledifficulty != 0) {
        Ran(20);
        if (mangledifficulty > RAN) {
          if (manglelocation < 9) {
            manglelocation++;
          }
          if (manglelocation == 5) {ventbanging = 1;}
        }
        manglelocationframe = manglelocationframelock;
    }

    if (night != 1) {
        if (officequeue[0] == 0 && lighthall == 0) {
            secondframefoxy--; 
            if (secondframefoxy == 0) {
                foxyalterablevalue++;
                secondframefoxy = 60;
            } 
        } else {secondframefoxy = 60;}

        if (officequeue[0] == 0 && ismaskon == 1 && toybonnielocation != 5 && toychicalocation != 6 && manglelocation != 6) {
            secondframefoxymask--; 
            if (secondframefoxymask == 0) {
                foxyalterablevalue++;
                secondframefoxymask = 60;
            } 
        } else {secondframefoxymask = 60;}

        if (lighthall == 1) {
            halfsecondframefoxy--; 
            if (halfsecondframefoxy == 0 && foxyalterablevalue > 0) {
                foxyalterablevalue--;
                halfsecondframefoxy = 30;
            } 
        } else {halfsecondframefoxy = 30;}

        if (foxylocation == 1) {
            if (lighthall == 1) {flashlightcounter++; foxyattackcounter = 50;}
            if (flashlightcounter > night * 100) {
                foxylocation--;
                flashlightcounter = 0;
                foxyalterablevalue = 0;
                foxyattackcounter = 500 + Ran(500);
                LightFuncHall();
            }
            if (foxyattackcounter > 0) {foxyattackcounter--;}

            if (foxyattackcounter == 0 && foxylocationframe == 0) {
                foxyreadyattack = 1;
            }
        }
    }

    if (foxylocationframe < 0 && foxydifficulty != 0)  {
        foxysran = (21 + Ran(5)) - foxyalterablevalue;
        if (foxydifficulty > foxysran && foxylocation == 0) {
            foxylocation++;
        }   
        foxylocationframe = foxylocationframelock;
    }
    if (GFdifficulty > 0) {
        if (GFlocationframehallway < 0) {
            if (lighthall == 0 && issomeonehall == 0) {
                Ran(10);
                if (RAN == 1) {
                    GFactivatedhallway = 1;
                    LoadTexture(_binary_tim_hallway_goldenhallway_tim_start, &animatronichallway);
                }
            }
            GFlocationframehallway = 60;
        }
        if (GFlocationframe < 0) {
            if (camera == 1) {
                Ran(20);
                if (GFdifficulty > RAN) {
                    GFnotactivatedyet = 1;
                    fadeGF = 128;
                }
            }
            GFlocationframe = 300;
        }
    }
    if (GFnotactivatedyet) {
        if (camera == 0) {GFactivated = 1; GFnotactivatedyet = 0;}
    }
    if (GFactivated) {
        if (lighthall == 1) {
            dead = 1;
            deadfrom = 9;
            GFactivated = 0;
        }
        if (camera == 1) { //If you raised down & up again but GF's here
            isalreadydeadlow = 1;
            GFactivated = 0;
        }
        if (ismaskon == 1) {
            GFdeactivating = 1;
            GFactivated = 0;
        }
    }
    if (GFdeactivating == 1) {
        if (fadeGF != 0) {fadeGF = fadeGF - 2;} else {GFdeactivating = 0;}
    }

    if (GFactivatedhallway == 1) {
        if (flashedonce == 1) {
            if (lighthall == 1) {
                GFscreamerhallway++;
                if (GFscreamerhallway == 100) {
                    dead = 1;
                    deadfrom = 9;
                }
            } else {
                GFscreamerhallway = 0;
                GFactivatedhallway = 0;
                flashedonce = 0;
            }
        } else {
            if (lighthall == 1) {flashedonce = 1;}
        }
    }
}
void screamer(void) {
    if (camera == 1) {
        CameraFunc(0);
    }  
    screamerframes--;
    
    if (spriteframes == 0) {
        spritesheet++;
        switch(deadfrom) {
            case 1: 
              if (spritesheet > 4) {SpuSetKey(SPU_OFF, SPU_06CH); menu = 3;} break;
            case 9:
                spriteframesconst = 1;
                break;
            default :
                if (spritesheet > 3) {SpuSetKey(SPU_OFF, SPU_06CH); menu = 3;} break;
        } 
        if (spritesheet > 4 && deadfrom == 2 || spritesheet > 4 && deadfrom == 3) {spritesheet = 0;}
        if (deadfrom != 9) {
            clearVRAMScreamer();
        }
        if (deadfrom == 1) {
          if (spritesheet == 1) {
              LoadTexture(_binary_tim_screamer_jumpF0_tim_start, &jumpscare);
          }
          if (spritesheet == 2) {
              LoadTexture(_binary_tim_screamer_jumpF1_tim_start, &jumpscare);
          }
          if (spritesheet == 3) {
              LoadTexture(_binary_tim_screamer_jumpF2_tim_start, &jumpscare);
          }
          if (spritesheet == 4) {
              LoadTexture(_binary_tim_screamer_jumpF3_tim_start, &jumpscare);
          }
          if (spritesheet == 5) {
              LoadTexture(_binary_tim_screamer_jumpF4_tim_start, &jumpscare);
          }
        }
        if (deadfrom == 2) {
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_jumpB2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_jumpB3_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamer_jumpB4_tim_start, &jumpscare);
            }
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_jumpB_tim_start, &jumpscare);
            } 
        }
        if (deadfrom == 3) {
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_Cjump2_tim_start, &jumpscare);
            }
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_Cjump4_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_Cjump5_tim_start, &jumpscare);
            }
            if (spritesheet == 0) {
                LoadTexture(_binary_tim_screamer_Cjump1_tim_start, &jumpscare);
            } 
        }
        if (deadfrom == 4) {
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_jumpFO_tim_start, &jumpscare);
            }
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_jumpFO2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_jumpFO3_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamer_jumpFO4_tim_start, &jumpscare);
            }
        }
        if (deadfrom == 5) {
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_jumpTF2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_jumpTF3_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamer_jumpTF4_tim_start, &jumpscare);
            }
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_jumpTF1_tim_start, &jumpscare);
            } 
        }
        if (deadfrom == 6) {
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_TBjump2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_TBjump4_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamer_TBjump5_tim_start, &jumpscare);
            }
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_TBjump1_tim_start, &jumpscare);
            } 
        }
        if (deadfrom == 7) {
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_TCjump2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_TCjump3_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamer_TCjump4_tim_start, &jumpscare);
            }
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_TCjump1_tim_start, &jumpscare);
            } 
        }
        if (deadfrom == 8) {
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_Mjump2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_Mjump4_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamer_Mjump5_tim_start, &jumpscare);
            }
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_Mjump1_tim_start, &jumpscare);
            } 
        }
        if (deadfrom == 9) {
            if (spritesheet == 1) {
                clearVRAMScreamer();
                LoadTexture(_binary_tim_screamer_jumpGF_tim_start, &jumpscare);
                ScaleVectorjump.vx = 1024;
                ScaleVectorjump.vy = 1624;
                MovVectorjump.vx = -20;
            } else {
                GFscaling = GFscaling + 448;
                MovVectorjump.vx = MovVectorjump.vx - 4;
                ScaleVectorjump.vx = GFscaling;
                ScaleVectorjump.vy = GFscaling + 600;
            }
        }
        if (deadfrom == 10) {
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_jumpP2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_jumpP3_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamer_jumpP5_tim_start, &jumpscare);
            }
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_jumpP1_tim_start, &jumpscare);
            } 
        }
        spriteframes = 4;
    } else {spriteframes--;}
    makepoly(14);
    if (screamerframes == 46) {
        SpuSetKey(SPU_OFF, SPU_ALLCH);
        SpuSetKey(SPU_ON, SPU_04CH);
    }
    if (screamerframes == 0) {
        menu = 3;
    }
}
void sideFunc(int number) {side = number;}
void LightFunc(void) {
    if (limiter2 == 0) {
        if (BBlol == 0) {
            if (side == 0) {
                light1++;
                if (light1 == 1) {
                    light2 = 0;
                    lighthall = 0;
                    LoadTexture(_binary_tim_office_oRIGHTpart2_tim_start, &officeRIGHT);
                    LoadTexture(_binary_tim_office_officeMIDDLE_tim_start, &officeMIDDLE); 
                    SpuSetKey(SPU_ON, SPU_00CH);
                    LoadTexture(_binary_tim_office_oLEFTpart2light_tim_start, &officeLEFTlight);
                }
                if (light1 >= 2) {
                    light1 = 0;
                    SpuSetKey(SPU_OFF, SPU_00CH);
                    LoadTexture(_binary_tim_office_oLEFTpart2_tim_start, &officeLEFT);                
                  }   
            }
            if (side == 1) {
                light2++;
                if (light2 == 1) {
                    light1 = 0;
                    lighthall = 0;
                    LoadTexture(_binary_tim_office_oLEFTpart2_tim_start, &officeLEFT);
                    LoadTexture(_binary_tim_office_officeMIDDLE_tim_start, &officeMIDDLE); 
                    LoadTexture(_binary_tim_office_oRIGHTpart2light_tim_start, &officeRIGHTlight);
                    SpuSetKey(SPU_ON, SPU_00CH);
                }
                if (light2 >= 2) {
                    light2 = 0;
                    SpuSetKey(SPU_OFF, SPU_00CH); 
                    LoadTexture(_binary_tim_office_oRIGHTpart2_tim_start, &officeRIGHT);
                } 
            }   
        } else {
            SpuSetKey(SPU_ON, SPU_18CH);
        }
        limiter2 = 1;
    }
}
void LightFuncHall(void) {
    if (limiterhall == 0) {
        if (BBlol == 0) {
            lighthall++;
            if (lighthall == 1) {
                if (flashlightbattery > 0) {
                    light1 = 0;
                    light2 = 0;
                    SpuSetKey(SPU_ON, SPU_00CH);
                    if (animatronicshallway[3]) { //Foxy
                        if (animatronicshallway[6]) { // + Mangle
                            LoadTexture(_binary_tim_hallway_foxanglhallway_tim_start, &animatronichallway);
                        } else { 
                            if (animatronicshallway[1]) { // + Bonnie
                            //LoadTexture(_binary_tim_hallway_foxbonnhallway_tim_start, &animatronichallway);
                            } else {
                                LoadTexture(_binary_tim_hallway_foxyhallway_tim_start, &animatronichallway);
                            }
                        }
                    } else {
                        if (animatronicshallway[4]) { // Toy freddy
                          LoadTexture(_binary_tim_hallway_toyfreddyhallway_tim_start, &animatronichallway); 
                        } else {
                            if (animatronicshallway[0]) { // Freddy
                                LoadTexture(_binary_tim_hallway_freddyhallway_tim_start, &animatronichallway); 
                            } else {
                                if (animatronicshallway[6]) { //Mangle
                                    LoadTexture(_binary_tim_hallway_manglehallway_tim_start, &animatronichallway); 
                                } else {
                                    if (animatronicshallway[1]) { //Bonnie
                                        LoadTexture(_binary_tim_hallway_bonniehallway_tim_start, &animatronichallway); 
                                    } else {
                                        if (animatronicshallway[5]) { //Toy chica
                                            LoadTexture(_binary_tim_hallway_toychicahallway_tim_start, &animatronichallway); 
                                        }
                                    }
                                }
                            }
                        }
                    }
                    LoadTexture(_binary_tim_office_oRIGHTpart2_tim_start, &officeRIGHT);
                    LoadTexture(_binary_tim_office_oLEFTpart2_tim_start, &officeLEFT);
                    LoadTexture(_binary_tim_office_officeMIDDLElight_tim_start, &officeMIDDLE); 

                    if (foxyreadyattack == 1) {
                        dead = 1;
                        deadfrom = 4;
                        foxyreadyattack = 0;
                    }
                } else {lighthall++;}
            }
            if (lighthall >= 2) {
                lighthall = 0;
                SpuSetKey(SPU_OFF, SPU_00CH); 
                LoadTexture(_binary_tim_office_officeMIDDLE_tim_start, &officeMIDDLE); 
            }
        } else {
            SpuSetKey(SPU_ON, SPU_18CH);
        }
        limiterhall = 1;
    }
}
void CameraFunc(int silent) {
    if (camlimiter == 0) {
        if (cooldowncamera == 0) {
            camera++;
            if (camera == 1) {
                if (toybonnielocation == 5) {
                    deadtoybonnie = 1;
                }
                if (silent == 0) {
                  SpuSetKey(SPU_OFF, SPU_01CH);
                  SpuSetKey(SPU_ON, SPU_07CH);
                }

                 //Disable lights
                if (light1 == 1) {
                  sideFunc(0);
                  LightFunc();

                }
                if (light2 == 1) {
                  sideFunc(1);
                  LightFunc();

                }
                if (lighthall == 1) {
                  LightFuncHall();
                }
                SpuSetKey(SPU_OFF, SPU_00CH);

                SpuSetVoiceVolume(2, 0x1800, 0x1800); //Lower down volume of officesound
            }
            if (camera >= 2) {
                camera = 0;
                if (deadtoybonnie == 1) {
                    dead = 1;
                    deadfrom = 6;
                }
                if (silent == 0) {
                  SpuSetKey(SPU_OFF, SPU_07CH);
                  SpuSetKey(SPU_ON, SPU_01CH);
                }

                SpuSetVoiceVolume(2, 0x2500, 0x2500); //Higher up volume of officesound
            }
            cooldowncamera = 15;
        }
    }
    camlimiter = 1;
}
void gamevictory(void) {
  if (camera == 1) {
    camera = 0;
  }
  SpuSetKey(SPU_OFF, SPU_ALLCH);
  LoadTexture(_binary_tim_5am6_FAM_tim_start, &fiveam); 
  FrameCounter++;
}
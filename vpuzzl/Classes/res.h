#ifndef __RES_MANAGE__TOOLS_H__
#define  __RES_MANAGE__TOOLS_H__

struct stageInfo{
	bool isLocked;
	int stageIndex;
};
extern int stageIndex;

static const char menu_sin[]			= "splayer.png";
static const char menu_sin_sel[]			= "splayer_sel.png";
static const char menu_mul[]			= "mplayer.png";
static const char menu_mul_sel[]			= "mplayer_sel.png";
static const char menu_about[]			= "about.png";
static const char menu_about_sel[]		= "about_sel.png";
static const char slogo[]			= "slogo.png";
static const char help[]			= "help.png";
static const char help_sel[]			= "help_sel.png";
static const char sound[]			= "sound.png";
static const char sound_disable[]			= "sound_disable.png";
static const char vlogo[]			= "vlogo.png";
static const char bg[]			= "bg.jpg";

static const char bgMusic[]			= "raw/titileMusic.mp3";
static const char item_sel_eff[] = "raw/item_sel_sound.mp3";

static const char back[]			= "back.png";
static const char back_sel[]			= "back_sel.png";
static const char level_pan[] = "level_pan.png";
static const char level_pan_side[] = "level_pan_side.png";
static const char stage[] = "thumbnail1.jpg";
static const char stage_sel[] = "thumbnail1_sel.png";
static const char locked[] = "locked.png";
static const char easy[] = "easy.png";
static const char easy_sel[] = "easy_sel.png";
static const char mid[] = "medium.png";
static const char mid_sel[] = "medium_sel.png";
static const char hard[] = "hard.png";
static const char hard_sel[] = "hard_sel.png";

static const char pausex[] = "pause.png";
static const char pause_sel[] = "pause_sel.png";
static const char back_ico[] = "back_ico.png";
static const char back_ico_sel[] = "back_ico_sel.png";
static const char magic1[] = "magic1.png";
static const char magic1_sel[] = "magic1_sel.png";
static const char magic_eff[] = "raw/magic_ative.mp3";

static const char contin[] = "continue.png";
static const char contin_sel[] = "continue_sel.png";
static const char restart[] = "restart.png";
static const char restart_sel[] = "restart_sel.png";
static const char mainMenu[] = "mainmenu.png";
static const char mainMenu_sel[] = "mainmenu_sel.png";

static const char desktop[] = "desktop.png";
static const char numberFont[] = "numbers.fnt";

static const char merge_Eff[] = "raw/merger.mp3";
static int ifFirstStart = true;
#endif							   

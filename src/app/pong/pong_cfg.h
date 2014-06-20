/*******************************************************************************************************************************
*	
*	Filename: pong_cfg.h
*	Rev Date: 5/2/2012
*
*	File Description:
*			Configuration file for Pong game
*
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define PONG_CFG_H_VERSION_MAJOR	(1)
#define PONG_CFG_H_VERSION_MINOR	(0)
#define PONG_CFG_H_VERSION_PATCH	(1)

/* Window Characteristics */
#define PONG_TOP_BORDER             (6)
#define PONG_BOTTOM_BORDER          (266)
#define PONG_LEFT_BORDER            (10)
#define PONG_RIGHT_BORDER           (470)

#define PONG_BORDER_COLOR           (RED)
#define PONG_BKGND_COLOR            (YELLOW)
#define PONG_GAME_COLOR             (BLACK)

/* Delay Timer */
#define PONG_RESTART_THRESHOLD      (50)
#define PONG_LONG_PRESS_DELAY       (1)
#define PONG_LONG_MOVE_NOT_OK       (0)
#define PONG_LONG_MOVE_OK           (1)
#define PONG_RIGHT_PAD_UPD_TIME     (0)
#define PONG_DELAY_TIMER            (3)

/* Paddle Characteristics */
#define PONG_PADDLE_WIDTH           (4)
#define PONG_PADDLE_HEIGHT          (20)
#define PONG_PADDLE_SPEED           (5)

#define LEFT_PADDLE_X_CTR           (14)
#define LEFT_PADDLE_Y_CTR           (136)
#define RIGHT_PADDLE_X_CTR          (466)
#define RIGHT_PADDLE_Y_CTR          (136)

#define PADDLE_NO_MOVE              (0)
#define PADDLE_MOVE_UP              (1)
#define PADDLE_MOVE_DOWN            (2)

/* Ball Characteristics */
#define PONG_BALL_CENTER_X          (240)
#define PONG_BALL_CENTER_Y          (136)
#define PONG_BALL_HEIGHT            (2)
#define PONG_BALL_WIDTH             (2)
#define PONG_BALL_SPEED             (5)

/* Direction Characteristics */
#define PONG_BALL_MOVE_RIGHT        (0)
#define PONG_BALL_MOVE_LEFT         (1)
#define PONG_BALL_MOVE_UP           (0)
#define PONG_BALL_MOVE_DOWN         (1)

/* Start Instruction Location */
#define PONG_TEXT_LOCX              (PONG_LEFT_BORDER + 180)
#define PONG_TEXT_LOCY              (PONG_BOTTOM_BORDER - 25)

/* Exit Parameters */
#define PONG_NO_PAUSE               (0)
#define PONG_PAUSE                  (1)


/* Sound Parameters */
#define PONG_AUDIO_NO_SOUND         (0)
#define PONG_AUDIO_BOUNCE           (1)
#define PONG_AUDIO_SCORE            (2)

#define PONG_BOUNCE_NUMOF_NOTES     (1)
#define PONG_SCORE_NUMOF_NOTES      (4)


/*******************************************************************************************************************************
*			Constant Definitions
*******************************************************************************************************************************/
const st_APP_PONG_SONG_Type st_tp_g_pong_bounce[PONG_BOUNCE_NUMOF_NOTES] =
{
	(U4)SPKR_NOTE_C4, (U4)10
};

const st_APP_PONG_SONG_Type st_tp_g_pong_score[PONG_SCORE_NUMOF_NOTES] =
{
	(U4)SPKR_NOTE_A6, (U4)10,
	(U4)SPKR_NOTE_B6, (U4)10,
	(U4)SPKR_NOTE_C7, (U4)10,
    (U4)SPKR_NOTE_D7, (U4)30
};



/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*   1.0.0		5/2/2012		J. Nabozny			Created
*   1.0.1       5/4/2012        J. Nabozny          Add Pong Sound
*
*******************************************************************************************************************************/

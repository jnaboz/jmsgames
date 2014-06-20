/*******************************************************************************************************************************
*	
*	Filename: pong.c
*	Rev Date: 5/2/2012
*
*	File Description:
*			Handle the gameplay for Pong
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "pong.h"
#include "pong_cfg.h"
#include "lpc_swim.h"
#include "iobtn.h"
#include "iojs.h"
#include "iospkr.h"


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define PONG_C_VERSION_MAJOR		(1)
#define PONG_C_VERSION_MINOR		(0)
#define PONG_C_VERSION_PATCH		(1)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/
static SWIM_WINDOW_T pongwin;
static U1 u1_s_pong_rfrsh;
static U1 u1_s_delay;

/* Pong Ball Variables */
static U2 u2_s_ball_xctr;
static U2 u2_s_ball_yctr;
static U1 u1_s_vert_dir;
static U1 u1_s_horiz_dir;

/* Left Paddle Variables */
static U2 u2_s_lt_pad_ctr;
static U1 u1_s_player_move;
static U1 u1_s_player_move_prev;
static U1 u1_s_long_press_tmr;

/* Right Paddle Variables */
static U2 u2_s_rt_pad_ctr;
static U1 u1_s_rt_pad_dir;
static U2 u2_s_rt_pad_tmr;

/* Game Start Flag */
static U1 u1_s_start_flag;
static U1 u1_s_restart_flag;
static U1 u1_s_restart_tmr;
static U1 u1_s_full_rfrsh_flag;

/* Pong Sound Variables */
static U1 u1_s_pong_audio_state;
static U4 u4_s_pong_audio_cntr;
static U4 u4_s_pong_curr_note;


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_AppPongInitScreen(void);
static void vd_s_AppPongRefresh(void);
static void vd_s_AppPongGameTask(void);
static void vd_s_AppPongRestart(void);
static void vd_s_AppPongUpdBall(void);
static void vd_s_AppPongCheckScore(void);
static void vd_s_AppPongScore(void);
static void vd_s_AppPongUpdLtPad(void);
static void vd_s_AppPongUpdMove(void);
static U1 u1_s_AppPongCheckMove(void);
static void vd_s_AppPongMoveLtPad(void);
static void vd_s_AppPongUpdRtPad(void);
static void vd_s_AppPongSetRtDir(void);
static void vd_s_AppPongMoveRtPad(void);
static void vd_s_AppPongUpdScreen(void);
static void vd_s_AppPongUpdateSound(void);
static void vd_s_AppPongStartSound(U1);
static void vd_s_AppPongBeginSound(U1);
static void vd_s_AppPongMatchUpd(U1);


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((PONG_C_VERSION_MAJOR == PONG_H_VERSION_MAJOR) && (PONG_C_VERSION_MAJOR == PONG_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((PONG_C_VERSION_MINOR == PONG_H_VERSION_MINOR) && (PONG_C_VERSION_MINOR == PONG_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((PONG_C_VERSION_PATCH == PONG_H_VERSION_PATCH) && (PONG_C_VERSION_PATCH == PONG_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppPongInitTask
*	Called By:				Initialization
*	Timing:					Initialization
*	Description:			Called to initialize pong screen
*
*******************************************************************************************************************************/
void vd_g_AppPongInitTask(void) 
{
    /* Initialize Ball Characteristics */
    u2_s_ball_xctr = (U2)PONG_BALL_CENTER_X;
    u2_s_ball_yctr = (U2)PONG_BALL_CENTER_Y;
    u1_s_vert_dir = (U1)PONG_BALL_MOVE_UP;
    u1_s_horiz_dir = (U1)PONG_BALL_MOVE_LEFT;

    /* Initialize Left Paddle */
    u2_s_lt_pad_ctr = (U2)LEFT_PADDLE_Y_CTR;
    u1_s_player_move = (U1)PADDLE_NO_MOVE;
    u1_s_player_move_prev = (U1)PADDLE_NO_MOVE;
    u1_s_long_press_tmr = (U1)0;

    /* Initialize Right Paddle */
    u2_s_rt_pad_ctr = (U2)RIGHT_PADDLE_Y_CTR;
    u1_s_rt_pad_dir = (U1)PADDLE_NO_MOVE;
    u2_s_rt_pad_tmr = (U2)0;

    /* Initialize Start Flag */
    u1_s_start_flag = (U1)0;
    u1_s_restart_flag = (U1)0;
    u1_s_restart_tmr = (U1)0;

    /* Initialize Audio Vars */
    u1_s_pong_audio_state = (U1)PONG_AUDIO_NO_SOUND;
    u4_s_pong_audio_cntr = (U4)0;
    u4_s_pong_curr_note = (U4)0;

    u1_s_full_rfrsh_flag = (U1)0;
    u1_s_delay = (U1)0;
    u1_s_pong_rfrsh = (U1)0;
    vd_s_AppPongInitScreen();
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongInitScreen
*	Called By:				Initialization
*	Timing:					Initialization
*	Description:			Called to initialize pong screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongInitScreen(void)
{
    swim_window_open(&pongwin, 480, 272, (COLOR_T *)FRAMEBUFFER_PRIMARY, 0, 0, 479, 271, 0, PONG_BORDER_COLOR, PONG_BKGND_COLOR, PONG_BORDER_COLOR);

    /* Draw Border */
    swim_put_box(&pongwin, 0, 0, PONG_LEFT_BORDER, 271);
    swim_put_box(&pongwin, 0, 0, 479, PONG_TOP_BORDER);
    swim_put_box(&pongwin, 0, PONG_BOTTOM_BORDER, 479, 271);
    swim_put_box(&pongwin, PONG_RIGHT_BORDER, 0, 479, 271);

    /* Draw Paddles and Ball */
    swim_set_pen_color(&pongwin, PONG_GAME_COLOR);
    swim_set_fill_color(&pongwin, PONG_GAME_COLOR);
    swim_put_box(&pongwin, (LEFT_PADDLE_X_CTR - PONG_PADDLE_WIDTH), (LEFT_PADDLE_Y_CTR - PONG_PADDLE_HEIGHT), (LEFT_PADDLE_X_CTR + PONG_PADDLE_WIDTH), (LEFT_PADDLE_Y_CTR + PONG_PADDLE_HEIGHT));
    swim_put_box(&pongwin, (RIGHT_PADDLE_X_CTR - PONG_PADDLE_WIDTH), (RIGHT_PADDLE_Y_CTR - PONG_PADDLE_HEIGHT), (RIGHT_PADDLE_X_CTR + PONG_PADDLE_WIDTH), (RIGHT_PADDLE_Y_CTR + PONG_PADDLE_HEIGHT));
    swim_put_box(&pongwin, (PONG_BALL_CENTER_X - PONG_BALL_WIDTH), (PONG_BALL_CENTER_Y - PONG_BALL_HEIGHT), (PONG_BALL_CENTER_X + PONG_BALL_WIDTH), (PONG_BALL_CENTER_Y + PONG_BALL_HEIGHT));
    vd_g_IoLcdSetBuffer(FRAMEBUFFER_PRIMARY);
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppPongTask10ms
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Update Pong Demo
*
*******************************************************************************************************************************/
void vd_g_AppPongTask10ms(void) 
{
    if((u1_s_pong_rfrsh & 0x80) != (U1)0)
    {
        vd_s_AppPongGameTask();
    }
    else
    {
        if((u1_s_pong_rfrsh & 0x7F) >= (U1)5)
        {
            vd_s_AppPongRefresh();
            u1_s_pong_rfrsh |= 0x80;
        }
        else
        {   
            u1_s_pong_rfrsh++;
        }
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongRefresh
*	Called By:				vd_g_AppPongTask10ms
*	Timing:					Sporadic
*	Description:		    Refresh Screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongRefresh(void)
{
    /* Clear Screen */
    swim_clear_screen(&pongwin, PONG_BKGND_COLOR);

    /* Refresh Border */
    swim_set_fill_color(&pongwin, PONG_BORDER_COLOR);
    swim_set_pen_color(&pongwin, PONG_BORDER_COLOR);
    swim_put_box(&pongwin, 0, 0, PONG_LEFT_BORDER, 272);
    swim_put_box(&pongwin, 0, 0, 480, PONG_TOP_BORDER);
    swim_put_box(&pongwin, 0, PONG_BOTTOM_BORDER, 480, 272);
    swim_put_box(&pongwin, PONG_RIGHT_BORDER, 0, 480, 272);

    /* Refresh Pieces */
    swim_set_pen_color(&pongwin, PONG_GAME_COLOR);
    swim_set_fill_color(&pongwin, PONG_GAME_COLOR);
    swim_put_box(&pongwin, (LEFT_PADDLE_X_CTR - PONG_PADDLE_WIDTH), (LEFT_PADDLE_Y_CTR - PONG_PADDLE_HEIGHT), (LEFT_PADDLE_X_CTR + PONG_PADDLE_WIDTH), (LEFT_PADDLE_Y_CTR + PONG_PADDLE_HEIGHT));
    swim_put_box(&pongwin, (RIGHT_PADDLE_X_CTR - PONG_PADDLE_WIDTH), (RIGHT_PADDLE_Y_CTR - PONG_PADDLE_HEIGHT), (RIGHT_PADDLE_X_CTR + PONG_PADDLE_WIDTH), (RIGHT_PADDLE_Y_CTR + PONG_PADDLE_HEIGHT));
    swim_put_box(&pongwin, (PONG_BALL_CENTER_X - PONG_BALL_WIDTH), (PONG_BALL_CENTER_Y - PONG_BALL_HEIGHT), (PONG_BALL_CENTER_X + PONG_BALL_WIDTH), (PONG_BALL_CENTER_Y + PONG_BALL_HEIGHT));

    /* Set Text */
    swim_put_text_xy(&pongwin, (const char*)"Press A to Start Game", PONG_TEXT_LOCX, PONG_TEXT_LOCY);
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongGameTask
*	Called By:				vd_g_AppPongTask10ms
*	Timing:					Sporadic
*	Description:		    Refresh Screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongGameTask(void)
{
    U1 u1_t_btn;

    if(u1_s_start_flag == (U1)TRUE)
    {
        if(u1_s_restart_flag == (U1)ON)
        {
            if(u1_s_delay >= (U1)PONG_DELAY_TIMER)
            {
                vd_s_AppPongUpdBall();
                vd_s_AppPongUpdLtPad();
                vd_s_AppPongUpdRtPad();
                vd_s_AppPongUpdScreen();

                u1_s_delay = (U1)0;
            }
            else
            {
                u1_s_delay++;
            }
        }
        else
        {
            vd_s_AppPongRestart();
        }
    }
    else
    {
        u1_t_btn = u1_g_IoGetBtnA();

        if(u1_t_btn == (U1)IO_BUTTON_PRESSED)
        {
            u1_s_start_flag = (U1)TRUE;
            swim_set_pen_color(&pongwin, PONG_BKGND_COLOR);
            swim_set_fill_color(&pongwin, PONG_BKGND_COLOR);
            swim_put_box(&pongwin, (PONG_TEXT_LOCX - 5), (PONG_TEXT_LOCY - 5), (PONG_RIGHT_BORDER - 1), (PONG_BOTTOM_BORDER - 1));
        }
    }

    vd_s_AppPongUpdateSound();
}


/*******************************************************************************************************************************
*	Function Name:		    u1_s_AppPongRestart
*	Called By:				vd_g_AppPongTask10ms
*	Timing:					Sporadic
*	Description:		    Wait timer to start ball moving
*
*******************************************************************************************************************************/
static void vd_s_AppPongRestart(void)
{
    if(u1_s_restart_tmr >= (U1)PONG_RESTART_THRESHOLD)
    {
        u1_s_restart_flag = (U1)ON;
        u1_s_restart_tmr = (U1)0;
    }
    else
    {
        u1_s_restart_tmr++;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongUpdBall
*	Called By:				vd_s_AppPongGameTask
*	Timing:					Sporadic
*	Description:		    Refresh Screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongUpdBall(void)
{
    switch(u1_s_horiz_dir)
    {
        case PONG_BALL_MOVE_RIGHT:

            u2_s_ball_xctr += PONG_BALL_SPEED;                                      /* Increment Ball Location */

            if(u2_s_ball_xctr >= (U2)PONG_RIGHT_BORDER)                             /* Ball Past Boundary ? */
            {
                u1_s_horiz_dir = PONG_BALL_MOVE_LEFT;                               /* Change Ball Direction */
                vd_s_AppPongScore();                                                /* Go to score reset function */
            }
            else if(u2_s_ball_xctr >= (U2)(RIGHT_PADDLE_X_CTR - PONG_PADDLE_WIDTH)) /* Ball at paddle location ? */
            {
                vd_s_AppPongCheckScore();                                           /* Check if a score or not */
            }

            break;

        case PONG_BALL_MOVE_LEFT:

            u2_s_ball_xctr -= PONG_BALL_SPEED;                                      /* Decrement Ball location */

            if(u2_s_ball_xctr <= (U2)PONG_LEFT_BORDER)                              /* Ball Past Boundary ? */
            {
                u1_s_horiz_dir = PONG_BALL_MOVE_RIGHT;                              /* Change Ball Direction */
                vd_s_AppPongScore();                                                /* Go to score reset function */
            }
            else if(u2_s_ball_xctr <= (U2)(LEFT_PADDLE_X_CTR + PONG_PADDLE_WIDTH))  /* Ball at paddle location ? */
            {
                vd_s_AppPongCheckScore();                                           /* Chekc if score or not */
            }

            break;
    }

    switch(u1_s_vert_dir)
    {
        case PONG_BALL_MOVE_UP:

            u2_s_ball_yctr -= PONG_BALL_SPEED;

            if((u2_s_ball_yctr - PONG_BALL_HEIGHT) <= (U2)PONG_TOP_BORDER)
            {
                u1_s_vert_dir = PONG_BALL_MOVE_DOWN;
                vd_s_AppPongStartSound((U1)PONG_AUDIO_BOUNCE);
            }

            break;

        case PONG_BALL_MOVE_DOWN:

            u2_s_ball_yctr += PONG_BALL_SPEED;

            if((u2_s_ball_yctr + PONG_BALL_HEIGHT) >= (U2)PONG_BOTTOM_BORDER)
            {
                u1_s_vert_dir = PONG_BALL_MOVE_UP;
                vd_s_AppPongStartSound((U1)PONG_AUDIO_BOUNCE);
            }

            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongCheckScore
*	Called By:				vd_s_AppPongUpdBall
*	Timing:					Sporadic
*	Description:		    Refresh Screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongCheckScore(void)
{
    U2 u2_t_top;
    U2 u2_t_bottom;

    u2_t_top = (u2_s_ball_yctr - PONG_BALL_HEIGHT);
    u2_t_bottom = (u2_s_ball_yctr + PONG_BALL_HEIGHT);

    switch(u1_s_horiz_dir)
    {
        case PONG_BALL_MOVE_RIGHT:

            if(
               (u2_t_bottom < (u2_s_rt_pad_ctr - PONG_PADDLE_HEIGHT)) ||        /* Ball Above Paddle ? */
               (u2_t_top > (u2_s_rt_pad_ctr + PONG_PADDLE_HEIGHT))              /* Ball Below Paddle ? */
               )
            {
                vd_s_AppPongScore();
            }
            else
            {
                u1_s_horiz_dir = (U1)PONG_BALL_MOVE_LEFT;
                vd_s_AppPongStartSound((U1)PONG_AUDIO_BOUNCE);
            }
            break;

        case PONG_BALL_MOVE_LEFT:

            if(
               (u2_t_bottom < (u2_s_lt_pad_ctr - PONG_PADDLE_HEIGHT)) ||        /* Ball Above Paddle ? */
               (u2_t_top > (u2_s_lt_pad_ctr + PONG_PADDLE_HEIGHT))              /* Ball Below Paddle ? */
               )
            {
                vd_s_AppPongScore();
            }
            else
            {
                u1_s_horiz_dir = (U1)PONG_BALL_MOVE_RIGHT;
                vd_s_AppPongStartSound((U1)PONG_AUDIO_BOUNCE);
            }

            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongScore
*	Called By:				vd_s_AppPongUpdBall
*	Timing:					Sporadic
*	Description:		    Refresh Screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongScore(void)
{
    u2_s_ball_xctr = (U2)PONG_BALL_CENTER_X;
    u2_s_ball_yctr = (U2)PONG_BALL_CENTER_Y;
    u2_s_lt_pad_ctr = (U2)LEFT_PADDLE_Y_CTR;
    u1_s_player_move = (U1)PADDLE_NO_MOVE;
    u1_s_player_move_prev = (U1)PADDLE_NO_MOVE;
    u2_s_rt_pad_ctr = (U2)RIGHT_PADDLE_Y_CTR;
    u1_s_rt_pad_dir = (U1)PADDLE_NO_MOVE;
    u1_s_restart_flag = (U1)0;
    u1_s_full_rfrsh_flag = (U1)ON;

    vd_s_AppPongStartSound((U1)PONG_AUDIO_SCORE);
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongUpdLtPad
*	Called By:				vd_s_AppPongGameTask
*	Timing:					Sporadic
*	Description:		    Refresh Screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongUpdLtPad(void)
{
    U1 u1_t_tmp;

    vd_s_AppPongUpdMove();
    u1_t_tmp = u1_s_AppPongCheckMove();

    if(u1_t_tmp == (U1)PONG_LONG_MOVE_OK)
    {
        vd_s_AppPongMoveLtPad();
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongUpdMove
*	Called By:				vd_s_AppPongGameTask
*	Timing:					Sporadic
*	Description:		    Update Joystick State for Paddle Movement
*
*******************************************************************************************************************************/
static void vd_s_AppPongUpdMove(void)
{
    u1_s_player_move = u1_g_IoGetJsState((U1)JS_LEFTY);

    if(
       (u1_s_player_move == (U1)FULLUP) || 
       (u1_s_player_move == (U1)HALFUP)
      )
    {
        u1_s_player_move = (U1)PADDLE_MOVE_UP;
    }
    else if(
            (u1_s_player_move == (U1)FULLDOWN) || 
            (u1_s_player_move == (U1)HALFUP)
            )
    {
        u1_s_player_move = (U1)PADDLE_MOVE_DOWN;
    }
    else
    {
        u1_s_player_move = (U1)PADDLE_NO_MOVE;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongCheckMove
*	Called By:				vd_s_AppPongGameTask
*	Timing:					Sporadic
*	Description:		    Check if josytick is in same state
*
*******************************************************************************************************************************/
static U1 u1_s_AppPongCheckMove(void)
{
    U1 u1_t_tmp;

    if(u1_s_player_move == u1_s_player_move_prev)
    {
        u1_s_long_press_tmr++;
        u1_t_tmp = (U1)PONG_LONG_MOVE_NOT_OK;

        if(u1_s_long_press_tmr >= PONG_LONG_PRESS_DELAY)
        {
            u1_t_tmp = (U1)PONG_LONG_MOVE_OK;
            u1_s_long_press_tmr = (U2)0;
        }
    }
    else
    {
        u1_t_tmp = (U1)PONG_LONG_MOVE_OK;
    }

    u1_s_player_move_prev = u1_s_player_move;

    return u1_t_tmp;
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongMoveLtPad
*	Called By:				vd_s_AppPongGameTask
*	Timing:					Sporadic
*	Description:		    Update Left Paddle Location
*
*******************************************************************************************************************************/
static void vd_s_AppPongMoveLtPad(void)
{
    switch(u1_s_player_move)
    {
        case PADDLE_MOVE_UP:

            u2_s_lt_pad_ctr -= PONG_PADDLE_SPEED;

            if((u2_s_lt_pad_ctr - PONG_PADDLE_HEIGHT) < PONG_TOP_BORDER)
            {
                u2_s_lt_pad_ctr = (U2)(PONG_TOP_BORDER + PONG_PADDLE_HEIGHT);
            }

            break;

        case PADDLE_MOVE_DOWN:

            u2_s_lt_pad_ctr += PONG_PADDLE_SPEED;

            if((u2_s_lt_pad_ctr + PONG_PADDLE_HEIGHT) > PONG_BOTTOM_BORDER)
            {
                u2_s_lt_pad_ctr = (U2)(PONG_BOTTOM_BORDER - PONG_PADDLE_HEIGHT);
            }

            break;

        case PADDLE_NO_MOVE:
        default:
            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongUpdRtPad
*	Called By:				vd_s_AppPongGameTask
*	Timing:					Sporadic
*	Description:		    Refresh Screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongUpdRtPad(void)
{
    vd_s_AppPongSetRtDir();
    vd_s_AppPongMoveRtPad();
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongSetRtDir
*	Called By:				vd_s_AppPongUpdRtPad
*	Timing:					Sporadic
*	Description:		    Set direction for right paddle
*
*******************************************************************************************************************************/
static void vd_s_AppPongSetRtDir(void)
{
    if(u2_s_rt_pad_ctr < u2_s_ball_yctr)
    {
        u1_s_rt_pad_dir = (U1)PADDLE_MOVE_DOWN;
    }
    else if(u2_s_rt_pad_ctr > u2_s_ball_yctr)
    {
        u1_s_rt_pad_dir = (U1)PADDLE_MOVE_UP;
    }
    else
    {
        u1_s_rt_pad_dir = (U1)PADDLE_NO_MOVE;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongMoveRtPad
*	Called By:				vd_s_AppPongUpdRtPad
*	Timing:					Sporadic
*	Description:		    Update Right Paddle Location
*
*******************************************************************************************************************************/
static void vd_s_AppPongMoveRtPad(void)
{

    if(u2_s_rt_pad_tmr >= (U2)PONG_RIGHT_PAD_UPD_TIME)
    {
        switch(u1_s_rt_pad_dir)
        {
            case PADDLE_MOVE_DOWN:

                u2_s_rt_pad_ctr += (U2)PONG_PADDLE_SPEED;

                if((u2_s_rt_pad_ctr + PONG_PADDLE_HEIGHT) > PONG_BOTTOM_BORDER)
                {
                    u2_s_rt_pad_ctr = (U2)(PONG_BOTTOM_BORDER - PONG_PADDLE_HEIGHT);
                }

                break;

            case PADDLE_MOVE_UP:

                u2_s_rt_pad_ctr -= (U2)PONG_PADDLE_SPEED;

                if((u2_s_rt_pad_ctr - PONG_PADDLE_HEIGHT) < PONG_TOP_BORDER)
                {
                    u2_s_rt_pad_ctr = (U2)(PONG_TOP_BORDER + PONG_PADDLE_HEIGHT);
                }

                break;

            case PADDLE_NO_MOVE:
            default:
                break;
        }

        u2_s_rt_pad_tmr = (U2)0;
    }
    else
    {
        u2_s_rt_pad_tmr++;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongUpdScreen
*	Called By:				vd_s_AppPongGameTask
*	Timing:					Sporadic
*	Description:		    Refresh Screen
*
*******************************************************************************************************************************/
static void vd_s_AppPongUpdScreen(void)
{   
    U2 u2_t_ball_x1;
    U2 u2_t_ball_y1;
    U2 u2_t_ball_x2;
    U2 u2_t_ball_y2;

    U2 u2_t_paddle_x1;
    U2 u2_t_paddle_x2;


    if(u1_s_full_rfrsh_flag == (U1)ON)
    {
        /* Clear Screen */
        swim_clear_screen(&pongwin, PONG_BKGND_COLOR);

        /* Draw Border */
        swim_set_pen_color(&pongwin, PONG_BORDER_COLOR);
        swim_set_fill_color(&pongwin, PONG_BORDER_COLOR);
        swim_put_box(&pongwin, 0, 0, PONG_LEFT_BORDER, 271);        /* Draw Left Border */
        swim_put_box(&pongwin, 0, 0, 479, PONG_TOP_BORDER);         /* Draw Top Border */
        swim_put_box(&pongwin, 0, PONG_BOTTOM_BORDER, 479, 271);    /* Draw Botton Border */
        swim_put_box(&pongwin, PONG_RIGHT_BORDER, 0, 479, 271);     /* Draw Right Border */

        u1_s_full_rfrsh_flag = (U1)OFF;
    }
    else
    {
        swim_set_pen_color(&pongwin, PONG_BORDER_COLOR);
        swim_set_fill_color(&pongwin, PONG_BORDER_COLOR);
        swim_put_box(&pongwin, 0, 0, PONG_LEFT_BORDER, 271);        /* Draw Left Border */
        swim_put_box(&pongwin, 0, 0, 479, PONG_TOP_BORDER);         /* Draw Top Border */
        swim_put_box(&pongwin, 0, PONG_BOTTOM_BORDER, 479, 271);    /* Draw Botton Border */
        swim_put_box(&pongwin, PONG_RIGHT_BORDER, 0, 479, 271);     /* Draw Right Border */

        swim_set_pen_color(&pongwin, PONG_BKGND_COLOR);
        swim_set_fill_color(&pongwin, PONG_BKGND_COLOR);

        swim_put_box(&pongwin, (PONG_LEFT_BORDER+1), (PONG_TOP_BORDER+1), (PONG_RIGHT_BORDER-1), (PONG_TOP_BORDER+20));

        /* Clear Ball */
        u2_t_ball_x1 = (u2_s_ball_xctr - (U2)(PONG_BALL_WIDTH + PONG_BALL_SPEED + 5));
        u2_t_ball_y1 = (u2_s_ball_yctr - (U2)(PONG_BALL_WIDTH + PONG_BALL_SPEED + 5));
        u2_t_ball_x2 = (u2_s_ball_xctr + (U2)(PONG_BALL_WIDTH + PONG_BALL_SPEED + 5));
        u2_t_ball_y2 = (u2_s_ball_yctr + (U2)(PONG_BALL_WIDTH + PONG_BALL_SPEED + 5));
        swim_put_box(&pongwin, u2_t_ball_x1, u2_t_ball_y1, u2_t_ball_x2, u2_t_ball_y2);

        /* Clear Left Paddle */
        u2_t_paddle_x1 = (U2)(LEFT_PADDLE_X_CTR - PONG_PADDLE_WIDTH);
        u2_t_paddle_x2 = (U2)(LEFT_PADDLE_X_CTR + PONG_PADDLE_WIDTH);
        swim_put_box(&pongwin, u2_t_paddle_x1, (PONG_TOP_BORDER + 1), u2_t_paddle_x2, (PONG_BOTTOM_BORDER - 1));

        /* Clear Right Paddle */
        u2_t_paddle_x1 = (U2)(RIGHT_PADDLE_X_CTR - PONG_PADDLE_WIDTH);
        u2_t_paddle_x2 = (U2)(RIGHT_PADDLE_X_CTR + PONG_PADDLE_WIDTH);
        swim_put_box(&pongwin, u2_t_paddle_x1, (PONG_TOP_BORDER + 1), u2_t_paddle_x2, (PONG_BOTTOM_BORDER - 1));
    }

    /* Rewrite Paddles and Ball */
    swim_set_pen_color(&pongwin, PONG_GAME_COLOR);
    swim_set_fill_color(&pongwin, PONG_GAME_COLOR);
    swim_put_box(&pongwin, (LEFT_PADDLE_X_CTR - PONG_PADDLE_WIDTH), (u2_s_lt_pad_ctr - PONG_PADDLE_HEIGHT), (LEFT_PADDLE_X_CTR + PONG_PADDLE_WIDTH), (u2_s_lt_pad_ctr + PONG_PADDLE_HEIGHT));  /* Draw Left Paddle */
    swim_put_box(&pongwin, (RIGHT_PADDLE_X_CTR - PONG_PADDLE_WIDTH), (u2_s_rt_pad_ctr - PONG_PADDLE_HEIGHT), (RIGHT_PADDLE_X_CTR + PONG_PADDLE_WIDTH), (u2_s_rt_pad_ctr + PONG_PADDLE_HEIGHT));  /* Draw Right Paddle */
    swim_put_box(&pongwin, (u2_s_ball_xctr - PONG_BALL_WIDTH), (u2_s_ball_yctr - PONG_BALL_HEIGHT), (u2_s_ball_xctr + PONG_BALL_WIDTH), (u2_s_ball_yctr + PONG_BALL_HEIGHT));  /* Draw Ball */
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongUpdateSound
*	Called By:				vd_s_AppPongGameTask
*	Timing:					Sporadic
*	Description:		    Update Note
*
*******************************************************************************************************************************/
static void vd_s_AppPongUpdateSound()
{
    switch(u1_s_pong_audio_state)
    {
        case PONG_AUDIO_BOUNCE:
            if(u4_s_pong_audio_cntr < st_tp_g_pong_bounce[(u4_s_pong_curr_note-(U4)1)].u4_note_length)
    		{
    			u4_s_pong_audio_cntr++;
    		}
    		else
    		{
    			if(u4_s_pong_curr_note >= (U4)PONG_BOUNCE_NUMOF_NOTES)
    			{
                    vd_g_AppPongStopSound();
    			}
    			else
    			{
    				vd_s_AppPongMatchUpd(PONG_AUDIO_BOUNCE);
    			}
    			u4_s_pong_audio_cntr = (U4)OFF;
    		}
            break;

        case PONG_AUDIO_SCORE:
            if(u4_s_pong_audio_cntr < st_tp_g_pong_score[(u4_s_pong_curr_note-(U4)1)].u4_note_length)
    		{
    			u4_s_pong_audio_cntr++;
    		}
    		else
    		{
    			if(u4_s_pong_curr_note >= (U4)PONG_SCORE_NUMOF_NOTES)
    			{
                    vd_g_AppPongStopSound();
    			}
    			else
    			{
    				vd_s_AppPongMatchUpd(PONG_AUDIO_SCORE);
    			}
    			u4_s_pong_audio_cntr = (U4)OFF;
    		}
            break;

        case PONG_AUDIO_NO_SOUND:
        default:
            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongStartSound
*	Called By:				Application
*	Timing:					Sporadic
*	Description:		    Update Note
*
*******************************************************************************************************************************/
static void vd_s_AppPongStartSound(U1 u1_a_tmp)
{
    u4_s_pong_audio_cntr = (U4)0;
    u4_s_pong_curr_note = (U4)0;
    u4_s_pong_audio_cntr = (U4)0;

    switch(u1_a_tmp)
    {
        case PONG_AUDIO_BOUNCE:
            u1_s_pong_audio_state = (U1)PONG_AUDIO_BOUNCE;
            break;

        case PONG_AUDIO_SCORE:
            u1_s_pong_audio_state = (U1)PONG_AUDIO_SCORE;
            break;

        case PONG_AUDIO_NO_SOUND:
        default:
            break;
    }

    vd_s_AppPongBeginSound(u1_s_pong_audio_state);
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongBeginSound
*	Called By:				Application
*	Timing:					Sporadic
*	Description:			Begin Sound
*
*******************************************************************************************************************************/
static void vd_s_AppPongBeginSound(U1 u1_a_state)
{
    vd_s_AppPongMatchUpd(u1_a_state);
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppPongMatchUpd
*	Called By:				Application
*	Timing:					Sporadic
*	Description:			Update Song Note
*
*******************************************************************************************************************************/
static void vd_s_AppPongMatchUpd(U1 u1_a_tmp)
{
    switch(u1_a_tmp)
    {
        case PONG_AUDIO_BOUNCE:
            vd_g_IoSpkrMatchUpd(st_tp_g_pong_bounce[u4_s_pong_curr_note].u4_note);
            u4_s_pong_curr_note++;
            break;

        case PONG_AUDIO_SCORE:
            vd_g_IoSpkrMatchUpd(st_tp_g_pong_score[u4_s_pong_curr_note].u4_note);
            u4_s_pong_curr_note++;
            break;

        case PONG_AUDIO_NO_SOUND:
        default:
            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppPongStopSound
*	Called By:				Application
*	Timing:					Sporadic
*	Description:			Stop Pong Sounds
*
*******************************************************************************************************************************/
void vd_g_AppPongStopSound(void)
{
    u4_s_pong_curr_note = (U4)0;
    u1_s_pong_audio_state = (U1)PONG_AUDIO_NO_SOUND;
    vd_g_IoSpkrStopSound();
}


/*******************************************************************************************************************************
*	Function Name:		    u1_g_AppPongPause
*	Called By:				StateMgr
*	Timing:					10ms
*	Description:			Check Pause state
*
*******************************************************************************************************************************/
U1 u1_g_AppPongPause(void)
{
    U1 u1_t_btn;

    u1_t_btn = u1_g_IoGetBtnStart();
    
    if(u1_t_btn == (U1)IO_BUTTON_PRESSED)
    {
        return PONG_PAUSE;
    }
    else
    {
        return PONG_NO_PAUSE;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppPongExit
*	Called By:				StateMgr
*	Timing:					10ms
*	Description:			Close Pong Window
*
*******************************************************************************************************************************/
void vd_g_AppPongExit(void)
{
    swim_window_close(&pongwin);
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev		Date		Author		Change Description
*	------	------		----------	------------------------------
*   1.0.0	5/2/2012	J. Nabozny	Created
*   1.0.1   5/4/2012    J. Nabozny  Add Sound
*
*******************************************************************************************************************************/


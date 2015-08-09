//
// breakout.c
//
// Computer Science 50
// Problem Set 3
// Programed by Henry Wan

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks and color options of bricks
#define ROWS 5
string COLORS[] = {"RED", "PINK", "YELLOW", "GREEN", "BLUE"};

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    double velocity_x = (-0.5 + drand48()) / 20.0;
    double velocity_y = (0.5 + drand48()) / 20.0;

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // wait for click before game start
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        // check the movement of paddle
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event);
                setLocation(paddle, x, HEIGHT - 80);
            }
        }
        // check the movement of the ball
        move(ball, velocity_x, velocity_y);

        if (getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0)
        { velocity_x = -velocity_x; }

        // bounce off left edge of window
        else if (getY(ball) <= 0)
        { velocity_y = -velocity_y; }
        else if (getY(ball) + getHeight(ball) >= HEIGHT)
        {
            lives--;
            while (getY(ball) != HEIGHT / 2 - RADIUS && lives > 0)
            {
                GEvent event = getNextEvent(MOUSE_EVENT);
                if (event != NULL)
                {
                    if (getEventType(event) == MOUSE_CLICKED)
                    {
                        setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);
                    }
                }   
            }
        }
        
        GObject object = detectCollision(window, ball);

        if (object != NULL)
        {
            if (strcmp(getType(object), "GRect") == 0)
            {
                double x = getX(ball);
                double y = getY(ball);
        
                if (object == getGObjectAt(window, x, y))
                {
                    if (object == getGObjectAt(window, x, y + 1))
                    { velocity_x = -velocity_x; }
                    else if (object == getGObjectAt(window, x + 1, y))
                    { velocity_y = -velocity_y; }
                    else
                    {
                        velocity_x = -velocity_x;
                        velocity_y = -velocity_y;  
                    }
                    
                    if (object != paddle)
                    {
                        bricks--;
                        points++;
                        updateScoreboard(window, label, points);
                        removeGWindow(window, object); 
                    }
                }
                else if (object == getGObjectAt(window, x + 2 * RADIUS, y))
                {
                    if (object == getGObjectAt(window, x + 2 * RADIUS, y + 1))
                    { velocity_x = -velocity_x; }
                    else if (object == getGObjectAt(window, x + 2 * RADIUS - 1, y))
                    { velocity_y = -velocity_y; }
                    else
                    {
                        velocity_x = -velocity_x;
                        velocity_y = -velocity_y;  
                    }
            
                    if (object != paddle)
                    {
                        bricks--;
                        points++;
                        updateScoreboard(window, label, points);
                        removeGWindow(window, object); 
                    }
                }
                else if (object == getGObjectAt(window, x, y + 2 * RADIUS))
                {
                    if (object == getGObjectAt(window, x, y + 2 * RADIUS - 1))
                    { velocity_x = -velocity_x; }
                    else if (object == getGObjectAt(window, x + 1, y + 2 * RADIUS))
                    { velocity_y = -velocity_y; }
                    else
                    {
                        velocity_x = -velocity_x;
                        velocity_y = -velocity_y;  
                    }
                    
                    if (object != paddle)
                    {
                        bricks--;
                        points++;
                        updateScoreboard(window, label, points);
                        removeGWindow(window, object); 
                    }
                }
                else if (object == getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS))
                {
                    if (object == getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS - 1))
                    { velocity_x = -velocity_x; }
                    else if (object == getGObjectAt(window, x + 2 * RADIUS - 1, y + 2 * RADIUS))
                    { velocity_y = -velocity_y; }
                    else
                    {
                        velocity_x = -velocity_x;
                        velocity_y = -velocity_y;  
                    }
            
                    if (object != paddle)
                    {
                        bricks--;
                        points++;
                        updateScoreboard(window, label, points);
                        removeGWindow(window, object); 
                    }
                }                
            }
        } 
    }  
    //wait for click before exiting
    waitForClick();

    //game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // display bricks on top of the window
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect rect = newGRect(j * WIDTH / 10 + 2, i * HEIGHT / 30 + 80, WIDTH / 10 - 4, HEIGHT / 30 - 4);
            setFilled(rect, true);
            setColor(rect, COLORS[i]);
            add(window, rect);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval circle = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS, 2 * RADIUS, 2 * RADIUS);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rect = newGRect(WIDTH / 2 - 30, HEIGHT - 80, 60, 8);
    setFilled(rect, true);
    setColor(rect, "BLACK");
    add(window, rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

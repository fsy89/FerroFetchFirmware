/*
  Animation.h - library for storing Animations for Fetch
  Copyright (c) 20019 Simen E. Sørensen. 
*/

// ensure this library description is only included once
#ifndef Animation_h
#define Animation_h

#include <Arduino.h>
#include <vector>

#define DUTY_CYCLE_RESOLUTION 20
//holders for infromation you're going to pass to shifting function
const int ALL_ROWS = 10;   //The total number of rows in the actual hardware
const int ALL_COLS = 19;   //The total number of columns in the actual hardware
const int ROWS = ALL_ROWS; //12; //The number of rows that are in use in the current program (different from ALL_ROWS in order to scale down the number of bits shifted out)
const int COLS = ALL_COLS; //21; //The number of cols that are in use in the current program (different from ALL_COLS in order to scale down the number of bits shifted out)

const int REGISTERS = ROWS;       // no of register series (indicating no of magnet-driver-PCBs connected to the Arduino)
const int BYTES_PER_REGISTER = 4; // no of 8-bit shift registers in series per line (4 = 32 bits(/magnets))

class Frame
{
public:
    Frame(uint32_t *picture = nullptr, uint8_t **duty_cycle = nullptr, int cols = COLS, int rows = ROWS);
    ~Frame();
    void        delete_frame(void);
    uint32_t*   get_picture();
    uint32_t    get_picture_at(int x);
    uint8_t**   get_duty_cycle();
    uint8_t     get_duty_cycle_at(int x, int y);
    void overwrite_duty_cycle(uint8_t** duty_cycle);
    void write_duty_cycle_at(int x, int y, uint8_t duty_cycle);
    void write_picture(uint32_t *picture);
    void write_pixel(int x, int y, bool state);
    void set_pixel(int x, int y);
    void clear_pixel(int x, int y);

    std::vector<int> pwm_pixels_x;
    std::vector<int> pwm_pixels_y;

private:
    int         _cols;
    int         _rows;

    uint8_t **  _duty_cycle;
    uint32_t *  _picture;

    void _delete_picture();
    void _delete_duty_cycle();
};

class Animation
{
public:
    Animation(Frame **frames = nullptr, int num_frames = 2, int cols = COLS, int rows = ROWS);
    void    delete_anim(void);
    Frame*  get_frame(int frame_num);
    void    set_frame(int frame_num, Frame* frame);
    void    load_frames_from_array(uint32_t** animation, uint8_t*** duty_cycle = nullptr);
    int     get_current_frame_num();
    void    goto_next_frame();
    Frame*  get_current_frame();
    Frame*  get_next_frame();
    Frame*  get_prev_frame();
private:
    int     _cols;
    int     _rows;
    int     _num_frames; 
    int     _current_frame;

    Frame **_frames;
    int     _get_next_frame_idx();
    int     _get_prev_frame_idx();
};

#endif
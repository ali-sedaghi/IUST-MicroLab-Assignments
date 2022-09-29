// Ali Sedaghi
// 97521378

#include <mega32.h>
#include <delay.h>
#include <glcd.h>
#include <font5x7.h>

void main(void) {
	int cx = 63;
	int cy = 31;
	int dir = 0;
	int r = 4;
	
	// Init
	GLCDINIT_t glcd_init_data;
	glcd_init_data.font = font5x7;
	glcd_init(&glcd_init_data);
    glcd_clear();
    delay_ms(50);
    
    // Name and student ID
    glcd_outtextxy(0, 0, "Ali Sedaghi");
    glcd_outtextxy(0, 53, "97521378");
    delay_ms(2000);
    glcd_clear();
    
    // House
    glcd_line(55, 63, 91, 63);
    glcd_line(91, 63, 91, 32);
    glcd_line(55, 63, 55, 32);
    glcd_line(55, 32, 45, 32);
    glcd_line(101, 32, 91, 32);
    glcd_line(73, 0, 101, 32);
    glcd_line(73, 0, 59, 14);
    glcd_line(52, 22, 45, 32);
    glcd_line(52, 22, 52, 7);
    glcd_line(59, 14, 59, 7);
    glcd_line(59, 7, 62, 7);
    glcd_line(52, 7, 49, 7);
    glcd_line(62, 7, 62, 3);
    glcd_line(49, 7, 49, 3);
    glcd_line(49, 3, 62, 3);
    delay_ms(2000);
    glcd_clear();
    
    while (1) {
        glcd_setcolor(0);
        glcd_circle(cx, cy, 4);
        
        if (dir == 0) {
            cy = cy - r;
            cx = cx + r;
            if (cx + r >= 127) {
                dir = 3;
            }
            if(cy - r <= 0) {
                dir = 1;
            }
        }
        else if (dir == 1) {
            cy = cy + r;
            cx = cx + r;
            if (cx + r >= 127) {
                dir = 2;
            }
            if(cy + r >= 63) {
                dir = 0;
            }
        }
        else if (dir == 2) {
            cy = cy + r;
            cx = cx - r;
            if (cx - r <= 0) {
                dir = 1;
            }
            if(cy + r >= 63) {
                dir = 3;
            }
        }
        else {
            cy = cy - r;
            cx = cx - r;
            if (cx - r <= 0) {
                dir = 0;
            }
            if (cy - r <= 0) {
                dir = 2;
            }
        }
        
        glcd_setcolor(1);
        glcd_circle(cx, cy, 4);
        delay_ms(50);
    }
}

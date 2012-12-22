#include <allegro.h>
#include <block.h>
#include <highscores.h>
#include <shape.h>
int main() 
{	
	allegro_init();
	install_keyboard();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 700, 0, 0);
	
	BITMAP *buffer = create_bitmap(640, 700);
	clear_to_color(buffer, 0x333333);
	
	rect(buffer, 1, 1, 51, 51, 0x21D059);
	rect(buffer, 2, 2, 50, 50, 0x21D059);
	rect(buffer, 3, 3, 49, 49, 0x21D059);
	
	textout_centre_ex(buffer, font, ALLEGRO_VERSION_STR, 320, 5, 0xFFFFFF, 0x333333);
	
	rectfill(buffer, 50, 100, 550, 600, 0xDF1680);
	
	blit(buffer, screen, 0, 0, 0, 0, 640, 700);
	
	readkey();
	
	destroy_bitmap(buffer);
	
	return 0;
}
END_OF_MAIN();

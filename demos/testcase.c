
#include <curses.h>

static void setup_colors();

int main()
{
    initscr();
    if (has_colors())
        setup_colors();

#ifdef PDCURSES
    PDC_set_title("Test case #32");
#endif

    int row = 0;
    for (int i = 0; i < 8; ++i) {
        WINDOW *w = derwin(stdscr, 1, COLS, row + i, 0);
        wattron(w, COLOR_PAIR(i));
        wprintw(w, "color%d", i);
        wattroff(w, COLOR_PAIR(i));
    }
    for (int i = 0; i < 8; ++i) {
        WINDOW *w = derwin(stdscr, 1, COLS, row + i + 9, 0);
        wattron(w, A_BOLD|COLOR_PAIR(i));
        wprintw(w, "color%d", i);
        wattroff(w, A_BOLD|COLOR_PAIR(i));
    }

    getch();

    endwin();

    return 0;
}

static void setup_colors()
{
    start_color();

    if (can_change_color()) {
        const unsigned tango_colors[16] = {
            0x2e3436, 0xcc0000, 0x4e9a06, 0xc4a000,
            0x3465a4, 0x75507b, 0x06989a, 0xd3d7cf,
            0x555753, 0xef2929, 0x8ae234, 0xf57900,
            0x729fcf, 0xad7fa8, 0x34e2e2, 0xeeeeec,
        };
        for (unsigned i = 0; i < 16; ++i) {
            unsigned color = tango_colors[i];
            unsigned r = (color >> 16) & 0xff;
            unsigned g = (color >> 8) & 0xff;
            unsigned b = (color >> 0) & 0xff;
            init_color(i, r * 1000 / 0xff, g * 1000 / 0xff, b * 1000 / 0xff);
        }
    }
    for (unsigned i = 0; i < 16; ++i)
        init_pair(i, i, COLOR_BLUE);
}

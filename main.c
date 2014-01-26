/*
Marcin Sza³aj
Warcaby
*/
#include <allegro.h>

void init();
void deinit();
void maluj();
void inicjalizacja();
int ruch(int k);
void pisanina();

BITMAP * plansza = NULL;
BITMAP * pionekBialy = NULL;
BITMAP * pionekCzarny = NULL;

    //Warcabnica. Tablica 8x8 reprezentuj¹ca warcabnicê
    int pole[8][8];
    //Odleglosc planszy od gornej krawedzi ekranu
    const int gora=50;
    //Odleglosc planszy od dolnej krawedzi ekranu
    const int lewo=50;
    //Szerkosc pola
    const int szer = 62;
    //definicje kolorow na warcabnicy
    const int bialy = 0, czarny = 1, pusty = 2;

int main() {
    init();

    int nr_ruchu = 0;
    char napis[30];

    show_mouse(screen);
    unscare_mouse();

    plansza = load_bmp("plansza.bmp", desktop_palette);

    if(!plansza)
    {
       set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
       allegro_message( "nie mogê za³adowaæ planszy!" );
       allegro_exit();
       return 0;
    }
    else
    {
       blit(plansza, screen, 0, 0, gora, lewo, plansza->w, plansza->h );
    }

    destroy_bitmap(plansza);

    clear_to_color(screen, makecol(211,176,92));
    pisanina();

    inicjalizacja();
    maluj();

    do
    {
        if(nr_ruchu%2)
        {
            ruch(czarny);
            textout_ex(screen, font, "---BIALYCH---", 600, 500, makecol(255,255,255), makecol(211,176,92));
        }
        else
        {
            ruch(bialy);
            textout_ex(screen, font, "---CZARNYCH--", 600, 500, makecol(0,0,0), makecol(211,176,92));
        }


        sprintf(napis, "numer ruchu: %d", nr_ruchu+1);
        textout_ex(screen, font, napis, 550, 450, makecol(0,0,0),makecol(211,176,92));

        nr_ruchu++;
    }while(mouse_b != 1);


	while (!key[KEY_ESC])
    {

    };


	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

//k - kolor
int ruch(int k)
{
    //zmienne w pikselach - gdzie znalazla sie myszka po wcisnieciu LPM i PPM
    int xp_LPM = 0, yp_LPM = 0, xp_PPM = 0, yp_PPM = 0;
    //zmienne ktorych zakres bedzie od 0 do 7 wskazujace logiczne polozenie na warcabnicy
    int x_LPM, y_LPM, x_PPM, y_PPM;

    while(mouse_b != 1)
    {
    };
    xp_LPM = mouse_x;
    yp_LPM = mouse_y;

    x_LPM = xp_LPM/szer-1;
    y_LPM = yp_LPM/szer-1;


    if(pole[x_LPM][y_LPM] != k)
    {
        allegro_message("graj swoimi pionami!");

    }

    while(mouse_b != 2)
    {
    };
    xp_PPM = mouse_x;
    yp_PPM = mouse_y;

    x_PPM = xp_PPM/szer-1;
    y_PPM = yp_PPM/szer-1;


    //-------   pola bezposrednie ----------//
    {
    //sprawdzenie pola lezacego po prawej w dol
    if(x_PPM == x_LPM+1 && y_PPM == y_LPM+1)
    {
        if(pole[x_PPM][y_PPM] == pusty)
        {
            pole[x_LPM][y_LPM] = pusty;
            pole[x_PPM][y_PPM] = k;
        }
        else
        {
            allegro_message("pole zajete");
        }
    }

    //sprawdzenie pola lezacego po lewej w dol
    if(x_PPM == x_LPM-1 && y_PPM == y_LPM+1)
    {
        if(pole[x_PPM][y_PPM] == pusty)
        {
            pole[x_LPM][y_LPM] = pusty;
            pole[x_PPM][y_PPM] = k;
        }
        else
        {
            allegro_message("pole zajete");
        }
    }

    //sprawdzenie pola lezacego po lewej w gore
    if(x_PPM == x_LPM-1 && y_PPM == y_LPM-1)
    {
        if(pole[x_PPM][y_PPM] == pusty)
        {
            pole[x_LPM][y_LPM] = pusty;
            pole[x_PPM][y_PPM] = k;
        }
        else
        {
            allegro_message("pole zajete");
        }
    }

    //sprawdzenie pola lezacego po prawej w gore
    if(x_PPM == x_LPM+1 && y_PPM == y_LPM-1)
    {
        if(pole[x_PPM][y_PPM] == pusty)
        {
            pole[x_LPM][y_LPM] = pusty;
            pole[x_PPM][y_PPM] = k;
        }
        else
        {
            allegro_message("pole zajete");
        }
    }
    }
    //-------KONIEC   pola bezposrednie ----------//



    //-------    pola na bicia ---------//
    {
    //sprawdzenie pola lezacego po prawej w dol
    //ostatni warunek sprawdza, czy miedzy polami stoi pion druzyny przeciwnej
    if(x_PPM == x_LPM+2 && y_PPM == y_LPM+2 && pole[x_LPM+1][y_LPM+1] == -k + 1)
    {
        if(pole[x_PPM][y_PPM] == pusty)
        {
            pole[x_LPM][y_LPM] = pusty;
            pole[x_PPM][y_PPM] = k;
            pole[x_LPM+1][y_LPM+1] = pusty;
        }
        else
        {
            allegro_message("pole zajete");
        }
    }

    //sprawdzenie pola lezacego po lewej w dol
    if(x_PPM == x_LPM-2 && y_PPM == y_LPM+2 && pole[x_LPM-1][y_LPM+1] == -k + 1)
    {
        if(pole[x_PPM][y_PPM] == pusty)
        {
            pole[x_LPM][y_LPM] = pusty;
            pole[x_PPM][y_PPM] = k;
            pole[x_LPM-1][y_LPM+1] = pusty;
        }
        else
        {
            allegro_message("pole zajete");
        }
    }

    //sprawdzenie pola lezacego po lewej w gore
    if(x_PPM == x_LPM-2 && y_PPM == y_LPM-2 && pole[x_LPM-1][y_LPM-1] == -k + 1)
    {
        if(pole[x_PPM][y_PPM] == pusty)
        {
            pole[x_LPM][y_LPM] = pusty;
            pole[x_PPM][y_PPM] = k;
            pole[x_LPM-1][y_LPM-1] = pusty;
        }
        else
        {
            allegro_message("pole zajete");
        }
    }

        //sprawdzenie pola lezacego po lewej w gore
    if(x_PPM == x_LPM+2 && y_PPM == y_LPM-2 && pole[x_LPM+1][y_LPM-1] == -k + 1)
    {
        if(pole[x_PPM][y_PPM] == pusty)
        {
            pole[x_LPM][y_LPM] = pusty;
            pole[x_PPM][y_PPM] = k;
            pole[x_LPM+1][y_LPM-1] = pusty;
        }
        else
        {
            allegro_message("pole zajete");
        }
    }


    }
    //-------KONIEC   pola na bicia-----//


    maluj();
    return(0);
}

void maluj()
{
    int x, y;

    plansza = load_bmp("plansza.bmp", desktop_palette);
    pionekCzarny = load_bmp("pionek-czarny.bmp", desktop_palette);
    pionekBialy = load_bmp("pionek-bialy.bmp", desktop_palette);

    blit(plansza, screen, 0, 0, gora, lewo, plansza->w, plansza->h );

    for(y=0; y<8; y++)
    {
        for(x=0; x<8; x++)
        {
            switch (pole[x][y])
            {
            case 0:
                masked_blit(pionekBialy, screen, 0, 0, gora + szer*x, lewo + szer*y, plansza->w, plansza->h );
                break;
            case 1:
                masked_blit(pionekCzarny, screen, 0, 0, gora + szer*x, lewo + szer*y, plansza->w, plansza->h );
                break;
            case 2:
                break;
            }

        }
    }

}

void inicjalizacja()
{
    int x, y;

    for(y=0; y<=7; y++)
        for(x=0; x<=7; x++)
        pole[x][y] = pusty;

    for(y=0; y<=2; y=y+2)
    {
       pole[x][y] = czarny;
       for(x=0; x<=8; x=x+2)
       {
          pole[x][y] = czarny;
       }
    }

    for(y=1; y<=2; y=y+2)
    {
       pole[x][y] = czarny;
       for(x=1; x<=8; x=x+2)
       {
          pole[x][y] = czarny;
       }
    }


    for(y=5; y<=7; y=y+2)
    {
       pole[x][y] = bialy;
       for(x=1; x<=8; x=x+2)
       {
          pole[x][y] = bialy;
       }
    }

    for(y=6; y<=6; y=y+2)
    {
       pole[x][y] = bialy;
       for(x=0; x<=8; x=x+2)
       {
          pole[x][y] = bialy;
       }
    }
}

void pisanina()
{
    const int wys_text = 20;
    int x_text = lewo+szer*8 + 10, y_text = gora+5;
    textout_ex(screen, font, "Witaj!", x_text, y_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "Jestem ulomnym, mlodziutkim", x_text, y_text + wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "programem do grania w warcaby.", x_text, y_text + 2*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "Potrafie juz calkiem duzo:", x_text, y_text + 3*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "- mozesz ruszac pionami i ja", x_text, y_text + 4*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "bede wiedzial kiedy dany ruch", x_text, y_text + 5*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "miales prawo wykonac", x_text, y_text + 6*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "- jesli trafi Ci sie bicie", x_text, y_text + 7*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "bede umial je przeprowadzic!", x_text, y_text + 8*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, " ", x_text, y_text + 9*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "Ale zaczynam sie gubic, kiedy", x_text, y_text + 10*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "ktos zaczyna grac nie fair.", x_text, y_text + 11*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "Dotyka nie swoich pionow,", x_text, y_text + 12*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "klika na MOJA szachownice...", x_text, y_text + 13*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "...no i nie potrafie sie", x_text, y_text + 14*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "...wylaczyc.", x_text, y_text + 15*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "Przepraszam. Jak bede starszy,", x_text, y_text +16*wys_text, makecol(0,0,0),-1);
    textout_ex(screen, font, "naucze sie tego wszystkiego.", x_text, y_text + 17*wys_text, makecol(0,0,0),-1);

    textout_ex(screen, font, "numer ruchu: 0", 550, 450, makecol(0,0,0),makecol(211,176,92));
    textout_ex(screen, font, "teraz kolej: ", 550, 480, makecol(0,0,0), makecol(211,176,92));
    textout_ex(screen, font, "---BIALYCH---", 600, 500, makecol(255,255,255), makecol(211,176,92));
    
    textout_ex(screen, font, "LPM - klikniecie na dany pionek", 55, 570, makecol(0,0,0), makecol(211,176,92));
    textout_ex(screen, font, "PPM - klikniecie na dane pole w ktorym ma sie znalezc pionek", 55, 580, makecol(0,0,0), makecol(211,176,92));
}


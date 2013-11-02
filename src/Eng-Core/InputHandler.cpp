#include <windows.h>
#include <stdio.h>
#include<conio.h>
#include<dos.h>

class UserInput
{
public:
	POINT getCursorPostion();
	char getPressedKey();


};
/**
 * returns a point object contains curso postion.
 */

POINT UserInput::getCursorPostion()
{
	
	POINT cursor;
GetCursorPos(&cursor);
return cursor;

}

char UserInput::getPressedKey()
{
	char keystroke= ')';
	if (kbhit())
{
	
    keystroke = getch();
    return keystroke;
}
	return keystroke;

}

/**
Working with some testes here to figure some stuff out.


  {
  int c;
  printf( "Press ENTER to continue... " );
  fflush( stdout );
  do c = getchar(); while ((c != '\n') && (c != EOF));
  }
int main ()
{

	UserInput input;
	POINT mouse = input.getCursorPostion();
	input.getPressedKey();
	std::cout << mouse.x << "," << mouse.y << "\n";


	PressEnterToContinue();

	return 0;
}


*/




/**
//Rob's comments
//This code is an example of getch being turned into chars that are readable
//The problem is getch stops the code till someone presses someting
//The fix for that is to use if(kbhit)

	 
	
	#define PAGE_UP     73
	#define HOME        71
	#define END         79
	#define PAGE_DOWN   81
	#define UP_ARROW    72
	#define LEFT_ARROW  75
	#define DOWN_ARROW  80
	#define RIGHT_ARROW 77
	#define F1          59
	#define F2          60
	#define F3          61
	#define F4          62
	#define F5          63
	#define F6          64
	#define F7          65
	#define F8          66
	#define F9          67
	#define F10         68
	#include <iostream>
	#include <conio.h>
	 
	using namespace std;
	 
	int main()	
	{
		unsigned char KeyStroke,c; unsigned int KStroke;
	 
		cout << "Press Escape to quit." << endl << endl;
	 
		do
		{
		c = char(getch());	KeyStroke =	c;   KStroke = int(KeyStroke);  
            
            if (KStroke == 72){cout << "UP ARROW" << endl;} 
            if (KStroke == 80){cout << "DOWN ARROW" << endl;}
            if (KStroke == 75){cout << "LEFT ARROW" << endl;} 
            if (KStroke == 77){cout << "RIGHT ARROW" << endl;}
            if (KStroke == 83){cout << "Delete" << endl;} 
            if (KStroke == 73){cout << "PAGE UP" << endl;}
            if (KStroke == 81){cout << "PAGE DOWN" << endl;} 
            if (KStroke == 71){cout << "HOME" << endl;} 
            if (KStroke == 79){cout << "END" << endl;}
            if (KStroke == 133){cout << "F11" << endl;} 
            if (KStroke == 134){cout << "F12" << endl;} 
            if (KStroke == 82){cout << "Insert" << endl;} 
            if (KStroke == 9){cout << "Tab" << endl;}
	        	        
			if (KeyStroke == 0)
			{
				KeyStroke = getch(); // Even though there are 2 getch() it reads one keystroke
				switch (KeyStroke)
				{
				case F1:
					cout << "F1" << endl;
					break;
				case F2:
					cout << "F2" << endl;
					break;
				case F3:
					cout << "F3" << endl;
					break;
				case F4:
					cout << "F4" << endl;
					break;
				case F5:
					cout << "F5" << endl;
					break;
				case F6:
					cout << "F6" << endl;
					break;
				case F7:
					cout << "F7" << endl;
					break;
				case F8:
					cout << "F8" << endl;
					break;
				case F9:
					cout << "F9" << endl;
					break;
				case F10:
					cout << "F10" << endl;
					break;
				default:
					cout << "Some other key." << endl;
				}
			}
			if((KeyStroke!=0)&&(KeyStroke!=72)&&(KeyStroke!=80)&&(KeyStroke!=75)&&(KeyStroke!=77)&&(KeyStroke!=83)&&(KeyStroke!=73)&&(KeyStroke!=81)&&(KeyStroke!=71)&&(KeyStroke!=79)&&(KeyStroke!=133)&&(KeyStroke!=134)&&(KeyStroke!=89)&&(KeyStroke!=9)){cout<<c<<endl;}
            
		} 
		while (KeyStroke != 27); // 27 = Escape key
	}


**/
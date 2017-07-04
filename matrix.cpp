#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <curses.h>



using namespace std;

int main()
{
	struct winsize w;

	ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);

	vector<vector<char> > scr(w.ws_col);
	for(int i=0;i<w.ws_col;i++)
	{
		scr[i].resize(w.ws_row);
	}
	srand(time(NULL));
	string cs(100,'c'), bs(100,' ');

	vector<string> masks(w.ws_col);
	for(int i=0;i<w.ws_col;i++)
	{
		masks[i]="";
	}
	for(int j=0;j<w.ws_col;j++)
	{
		for(int i=0;i<100;i++)
		{
			int len = rand()%50;
			
			if(i%2==1)
			{
				masks[j] += cs.substr(0,len);
			}
			else
			{
				masks[j] += bs.substr(0,len);
			}
		}
	}


	for(int j=0;j<w.ws_col;j++)
	{
		for(int i=0;i<w.ws_row;i++)
		{
			
			scr[j][i]=' ';
		}
	}

	vector<int> pos(w.ws_col);
	for(int i=0;i<w.ws_col;i++)pos[i]=0;

	WINDOW *mainwin;

	if((mainwin = initscr())==NULL)
	{
		cout<<"error occured"<<endl;
		return 0;
	}


	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	attron(COLOR_PAIR(1));

	while(true)
	{

		for(int i=0;i<w.ws_col;i++)
		{
			for(int j=0;j<w.ws_row;j++)
			{
				mvaddch(j,i,scr[i][j]);
			}
		}
		refresh();
		for(int i=0;i<w.ws_col;i++)
		{
			int x=pos[i];
			for(int j=w.ws_row-1;j>0;j--)
			{
				if(scr[i][j-1]==' ')
				{
					scr[i][j]=' ';
				}
				else if(scr[i][j-1]!=' '&&scr[i][j]==' ')
				{
					int in = rand()%94 + 33;
					scr[i][j]=char(in);
				}
			}
			if(masks[i][pos[i]]==' ')
			{
				scr[i][0]=' ';
			}
			else if(masks[i][pos[i]]=='c'&&scr[i][0]==' ')
			{
				int in = rand()%94 + 33;
				scr[i][0]=char(in);
			}
			pos[i]++;
			if(pos[i]==masks[i].length())pos[i]=0;
		}
		usleep(40000);

	}



}
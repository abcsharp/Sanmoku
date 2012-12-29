#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <Windows.h>

template<typename T> void resetgrid(T& grid)
{
	for(auto& row:grid)
		for(auto& cell:row)
			cell=0;
}

template<typename T> void showgrid(const T& grid)
{
	std::cout<<' ';
	for(int i=1;i<=grid[0].size();++i) std::cout<<i;
	std::cout<<std::endl;
	for(int i=0;i<grid.size();++i){
		std::cout<<i+1;
		for(const auto& cell:grid[i])
			std::cout<<(cell==0?' ':cell==1?'O':'X');
		std::cout<<std::endl;
	}
}

template<typename T> int checkwinning(const T& grid,int x,int y)
{
	int a=0,b=0;
	for(int i=0;i<grid[y].size()&&a<3&&b<3;++i){
		if(grid[y][i]==1) ++a,b=0;
		else if(grid[y][i]==2) a=0,++b;
		else a=0,b=0;
	}
	if(a>=3) return 1;
	else if(b>=3) return 2;
	a=0,b=0;
	for(int i=0;i<grid[y].size()&&a<3&&b<3;++i){
		if(grid[i][x]==1) ++a,b=0;
		else if(grid[i][x]==2) a=0,++b;
		else a=0,b=0;
	}
	if(a>=3) return 1;
	else if(b>=3) return 2;
	a=0,b=0;
	int c=-(std::min)(x,y);
	while(x+c<grid[0].size()&&y+c<grid.size()&&a<3&&b<3){
		if(grid[y+c][x+c]==1) ++a,b=0;
		else if(grid[y+c][x+c]==2) a=0,++b;
		else a=0,b=0;
		++c;
	}
	if(a>=3) return 1;
	else if(b>=3) return 2;
	a=0,b=0,c=0;
	while(x-c<grid.size()-1&&y+c>0) --c;
   	while(x-c>=0&&y+c<grid.size()&&a<3&&b<3){
		if(grid[y+c][x-c]==1) ++a,b=0;
		else if(grid[y+c][x-c]==2) a=0,++b;
		else a=0,b=0;
		++c;
	}
	if(a>=3) return 1;
	else if(b>=3) return 2;
	return 0;
}

void ClearConsole(void)
{
	auto stdHandle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo={0};
	GetConsoleScreenBufferInfo(stdHandle,&consoleInfo);
	int bufferSize=consoleInfo.dwSize.X*consoleInfo.dwSize.Y;
	DWORD writtenSize;
	COORD zero={0};
	FillConsoleOutputCharacter(stdHandle,L' ',bufferSize,zero,&writtenSize);
	SetConsoleCursorPosition(stdHandle,zero);
}

int main(void)
{
	std::vector<std::vector<int> > grid(5,std::vector<int>(5));
	std::string playernames[2],replayanswer;
	for(int i=0;i<sizeof(playernames)/sizeof(std::string);++i){
		std::cout<<i+1<<"人目の名前を入力してください>";
		std::cin>>playernames[i];
	}
	do{
		resetgrid(grid);
		int turn=std::rand()%2,x=0,y=0;
		while(1){
			ClearConsole();
			int checkresult=checkwinning(grid,x,y);
			if(checkresult){
				std::cout<<playernames[checkresult-1]<<"さんの勝ちです。"<<std::endl;
				showgrid(grid);
				break;
			}
			std::cout<<"-----"<<playernames[turn]<<"さんの番です-----"<<std::endl;
			showgrid(grid);
			while(1){
				std::cout<<"マークする座標を入力してください>";
				std::cin>>x>>y;
				x-=1;
				y-=1;
				if(x>=0&&x<grid[0].size()&&y>=0&&y<grid.size()){
					if(!grid[y][x]){
						grid[y][x]=turn+1;
						break;
					}else{
						std::cout<<"その場所はすでにマークされています。もう一度入力してください。"<<std::endl;
						continue;
					}
				}else{
					std::cout<<"入力された座標は間違っています。もう一度入力してください。"<<std::endl;
					continue;
				}
			}
			turn=(turn?0:1);
		}
		std::cout<<"もう一回ゲームをやりますか?(y/n)>";
		std::cin>>replayanswer;
	}while(std::tolower(replayanswer[0])=='y');
	return 0;
}

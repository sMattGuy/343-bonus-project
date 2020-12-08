#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main(){
	string input = "";
	while(input != "Q"){
		string instructionformat = "";
		string operation = "";
		int sourcereg = 0;
		int sourcereg2 = 0;
		int destinationreg = 0;
		int shift = 0;
		int constoffset = 0;
		bool hasshift = false;
		bool hasconsoff = false;
		bool doublesource = false;
		bool hassource = true;
		bool hasdestination = true;
		
		cout<<"Enter Binary String (Q to quit)"<<endl;
		cout<<"input:";
		cin>>input;
		if(input == "Q")
			return 0;
		int format = 0;
		//get format bits
		for(int i=0;i<=5;i++){
			format += ((int(input[i])-48) * pow(2, 5-i));
		}
		//r type
		if(format == 0){
			doublesource = true;
			hasshift = true;
			instructionformat = "R";
			//source reg rs
			for(int i=6;i<=10;i++){
				sourcereg += ((int(input[i])-48) * pow(2, 10-i));
			}
			//second reg opperand
			for(int i=11;i<=15;i++){
				sourcereg2 += ((int(input[i])-48) * pow(2, 15-i));
			}
			//destination reg
			for(int i=16;i<=20;i++){
				destinationreg += ((int(input[i])-48) * pow(2, 20-i));
			}
			//shift
			for(int i=21;i<=25;i++){
				shift += ((int(input[i])-48) * pow(2, 25-i));
			}
			//function
			int opcode = 0;
			for(int i=26;i<=31;i++){
				opcode += ((int(input[i])-48) * pow(2, 31-i));
			}
			switch(opcode){
				case 0:
				operation = "sll";
				break;
				case 2:
				operation = "srl";
				break;
				case 8:
				operation = "jr";
				break;
				case 32:
				operation = "add";
				break;
				case 33:
				operation = "addu";
				break;
				case 34:
				operation = "sub";
				break;
				case 35:
				operation = "subu";
				break;
				case 36:
				operation = "and";
				break;
				case 37:
				operation = "or";
				break;
				case 39:
				operation = "nor";
				break;
				case 42:
				operation = "slt";
				break;
				case 43:
				operation = "sltu";
				break;
				default:
				cout<<"error has occured in r type\n";
				return 0;
			}
		}
		//i type
		else if(format > 3){
			instructionformat = "I";
			hasconsoff = true;
			switch(format){
				case 4:
				hasconsoff = true;
				break;
				case 5:
				operation = "bne";
				hasconsoff = true;
				break;
				case 8:
				operation = "addi";
				break;
				case 9:
				operation = "addiu";
				break;
				case 10:
				operation = "slti";
				break;
				case 11:
				operation = "sltiu";
				break;
				case 12:
				operation = "andi";
				break;
				case 13:
				operation = "ori";
				break;
				case 15:
				operation = "lui";
				break;
				case 35:
				operation = "lw";
				hasconsoff = true;
				break;
				case 43:
				operation = "sw";
				hasconsoff = true;
				break;
				default:
				cout<<"error has occured in i type\n";
				return 0;
			}
			//source reg rs
			for(int i=6;i<=10;i++){
				sourcereg += ((int(input[i])-48) * pow(2, 10-i));
			}
			//destination reg rt
			for(int i=11;i<=15;i++){
				destinationreg += ((int(input[i])-48) * pow(2, 15-i));
			}
			//immediate
			for(int i=16;i<=31;i++){
				constoffset += ((int(input[i])-48) * pow(2, 31 - i));
			}
		}
		//j type
		else{
			switch(format){
				case 2:
				instructionformat = "J";
				operation = "j";
				break;
				case 3:
				instructionformat = "J";
				operation = "jal";
				break;
			}
			hassource = false;
			hasdestination = false;
			//const
			for(int i=7;i<=31;i++){
				constoffset += ((int(input[i])-48) * pow(2, i-7));
			}
		}
		//printout
		cout<<"Outputs:"<<endl;
		cout<<"Instruction Format:"<<instructionformat<<endl;
		cout<<"Operation:"<<operation<<endl;
		if(doublesource)
			cout<<"Source Registers:"<<sourcereg<<", "<<sourcereg2<<endl;
		else if(hassource)
			cout<<"Source Register:"<<sourcereg<<endl;
		else
			cout<<"Source Register:none\n";
		cout<<"Destination Register:"<<destinationreg<<endl;
		if(hasshift)
			cout<<"Shift Amount:"<<shift<<endl;
		else
			cout<<"Shift Amount:none\n";
		if(hasconsoff)
			cout<<"Constant/Offset:"<<constoffset<<endl;
		else
			cout<<"Constant/Offset:none\n";
		cout<<"\n\n";
	}
	return 0;
}
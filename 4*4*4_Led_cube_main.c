/*
 * main.c
 *
 *  Created on: Feb 23, 2021
 *      Author: marof
 */


#include <avr/io.h>
#include <avr/delay.h>

#define F_CPU 16000000UL

const uint8_t Write_HIGH[] ={(1<<PD0) ,(1<<PD1),(1<<PD2),(1<<PD3) ,(1<<PD4) ,(1<<PD5) ,(1<<PD6) ,
		(1<<PD7) ,(1<<PB0),(1<<PB1),(1<<PB2),(1<<PB3),(1<<PB4),(1<<PB5),(1<<PC4),(1<<PC5)
		//0b00000001,//PORTD |= (1<<PD0) ,//0
		//0b00000010,//PORTD |= (1<<PD1),//1
	//	0b00000100,//PORTD |= (1<<PD2),//2
		//0b00001000,//PORTD |= (1<<PD3) ,//3
		//0b00010000,//PORTD |= (1<<PD4),//4
		//0b00100000,//PORTD |= (1<<PD5),//5
		//0b01000000,//PORTD |= (1<<PD6),//6
		//0b10000000,//PORTD |= (1<<PD7),//7
		//0b00000001,//PORTB |= (1<<PB0),//8
		//0b00000010,//PORTB |= (1<<PB1),//9
		//0b00000100,//PORTB |= (1<<PB2),//10
		//0b00001000,//PORTB |= (1<<PB3),//11
		//0b00010000,//PORTB |= (1<<PB4),//12
		//0b00100000,//PORTB |= (1<<PB5),//13

		//0b00001000,//PORTC |= (1<<PC4),//A4
		//0b00010000,//PORTC |= (1<<PC5)//A5
};
const uint8_t Write_LOW[] ={(1<<PD0) ,(1<<PD1),(1<<PD2),(1<<PD3) ,(1<<PD4) ,(1<<PD5) ,(1<<PD6) ,
		(1<<PD7) ,(1<<PB0),(1<<PB1),(1<<PB2),(1<<PB3),(1<<PB4),(1<<PB5),(1<<PC4),(1<<PC5)

	/*	0b00000000,//PORTD &=~ (1<<PD0) ,//0
		0b00000000,//PORTD &=~ (1<<PD1),//1
		0b00000000,//PORTD &=~ (1<<PD2),//2
		0b00000000,//PORTD &=~ (1<<PD3) ,//3
		0b00000000,//PORTD &=~ (1<<PD4),//4
		0b00000000,//PORTD &=~ (1<<PD5),//5
		0b00000000,//PORTD &=~ (1<<PD6),//6
		0b00000000,//PORTD &=~ (1<<PD7),//7
		0b00000000,//PORTB &=~ (1<<PB0),//8
		0b00000000,//PORTB &=~ (1<<PB1),//9
		0b00000000,//PORTB &=~ (1<<PB2),//10
		0b00000000,//PORTB &=~ (1<<PB3),//11
		0b00000000,//PORTB &=~ (1<<PB4),//12
		0b00000000,//PORTB &=~ (1<<PB5),//13

		0b00000000,//PORTC &=~ (1<<PC4),//A4
		0b00000000,//PORTC &=~ (1<<PC5)//A5*/
};
const uint8_t Layer_HIGH[]={(1<<PC0),(1<<PC1),(1<<PC2),(1<<PC3)

	/*	0b00000001,//PORTC |=(1<<PC0),//A0
		0b00000010,//PORTC |=(1<<PC1),//A1
		0b00000100,//PORTC |=(1<<PC2),//A2
		0b00001000,//PORTC |=(1<<PC3),//A3 */
};
const uint8_t Layer_LOW[]={(1<<PC0),(1<<PC1),(1<<PC2),(1<<PC3)

		/*0b00000000,//PORTC &=~(1<<PC0),//A0
		0b00000000,//PORTC &=~(1<<PC3),//A3
		0b00000000,//PORTC &=~(1<<PC1),//A1
		0b00000000,//PORTC &=~(1<<PC2),//A2 */
};


	//Following will have same effect
	//DDRD |= (1<<DDD6)|(1<<DDD5)|(1<<DDD4)|(1<<DDD3)|(1<<DDD2)|(1<<DDD1)|(1<<DDD0);
	//DDRD |= _BV(DDD6)|_BV(DDD5)|_BV(DDD4)|_BV(DDD3)|_BV(DDD2)|_BV(DDD1)|_BV(DDD0);

	//uint8_t i;

		//for(i=0;i<15;i++)
		//{
		//	PORTD= segment_look_up[i];
		//	_delay_ms(2000);
	//	}

		//turnEverythingOff
		void turnEverythingOff(){
			PORTD=0xFF;
		PORTC= 0x30; //0b00110000
		PORTB= 0xFF;

		}
		//turnEverythingOn
		void turnEverythingOn(){
			PORTD = 0x00;
			PORTC |=(1<<PC0);//A0
		    PORTC |=(1<<PC1);//A1
			PORTC |=(1<<PC2);//A2
			PORTC |=(1<<PC3);//A3
			//PORTC = 0x0F;
			PORTC &=~ (1<<PC4);
			PORTC &=~ (1<<PC5);
			PORTB &=~ (1<<PB0);
			PORTB &=~ (1<<PB1);
			PORTB &=~ (1<<PB2);
			PORTB &=~ (1<<PB3);
			PORTB &=~ (1<<PB4);
			PORTB &=~ (1<<PB5);

		}
		//turnColumnsOff
		void turnColumnsOff(){
			PORTD = 0xFF;
			PORTC |= (1<<PC5)|(1<<PC4);
			PORTB = 0xFF;

		}
		//flicker on
		void flickerOn(){
			int j =150;
			while(j !=0){
				turnEverythingOn();
				_delay_ms(200);
				turnEverythingOff();
				_delay_ms(150);
				j-=5;
			}
		}
		//turn everything on and off by layer up and down NOT TIMED
		void turnOnAndOffAllByLayerUpAndDownNotTimed(){
			int x =75;
			for (int i=4;i!=0;i--){
				turnEverythingOn();
				for(int i=4;i!=0;i--){
					PORTC &=~ Layer_LOW[i-1];
					_delay_ms(x);
				}
				for(int i=0;i<4;i++){
					PORTC |= Layer_HIGH[i];
					_delay_ms(x);
				}
				for(int i=0;i<4;i++){
					PORTC &=~ Layer_LOW[i];
					_delay_ms(x);
				}
				for(int i=4;i!=0;i--){
					PORTC |= Layer_HIGH[i-1];
					_delay_ms(x);
				}
			}
		}

		//turn everything on and off by column sideways
		void turnOnAndOffAllByColumnSideways(){
			int x=100;
			turnEverythingOff();
			//turn on layers
			for(int i = 0; i<4; i++)
			  {
				PORTC |= Layer_HIGH[i];
			  }



			for(int y=0;y<3;y++){
				//turn on 0-3

				for(int i=0;i<4;i++){
					PORTD &=~ Write_LOW[i];
					_delay_ms(x);
				}
				//turn on 4-7

				for(int i=4;i<8;i++){
					PORTD &=~ Write_LOW[i];
					_delay_ms(x);
				}
				//turn on 8-11
				    for(int i = 8; i<12; i++)
				    {
				     PORTB &=~ Write_LOW[i];
				      _delay_ms(x);
				    }
				    //turn on 12-15
				   for(int i=12;i<14;i++)
				   {
				    	PORTB &=~ Write_LOW[i];
				    	PORTC &=~ Write_LOW[14];
				    	PORTC &=~ Write_LOW[15];
				    	_delay_ms(x);
				   }


				   //turn off 0-3
				   	for(int i=0;i<4;i++)
				   	{
				    	PORTD |= Write_HIGH[i];
				   	   _delay_ms(x);
				   	}
				   	//turn off 4-7
				   	for(int i=4;i<8;i++)
				   	{
				    	PORTD |= Write_HIGH[i];
				   		_delay_ms(x);
				   	}
				   	//turn off 8-11
				   	 for(int i = 8; i<12; i++)
				   	 {
				   		 PORTB |= Write_HIGH[i];
				   		  _delay_ms(x);
				   	 }
				     //turn off 12-15
				   	for(int i=12;i<14;i++)
				    {
				   		PORTB |= Write_HIGH[i];
				   		PORTC |= Write_HIGH[14];
				   		PORTC |= Write_HIGH[15];
				    	_delay_ms(100);
				    }
				    //turn on 12-15
				    for(int i=12;i<14;i++)
				    {
				    	PORTB &=~ Write_LOW[i];
				    	PORTC &=~ Write_LOW[14];
				    	PORTC &=~ Write_LOW[15];
				    	_delay_ms(x);
				    }
				   	//turn on 8-11
				    for(int i = 8; i<12; i++)
				    {
				   	  PORTB &=~ Write_LOW[i];
				   	   _delay_ms(x);
				    }
				    //turn on 4-7
		    		for(int i=4;i<8;i++)
				   	{
				   		PORTD &=~ Write_LOW[i];
				   		_delay_ms(x);
				   	}
				   	//turn on 0-3
				   	for(int i=0;i<4;i++)
				   	{
				     PORTD &=~ Write_LOW[i];
				   	 _delay_ms(x);
				    }
				    //turn off 12-15
				 	for(int i=12;i<14;i++)
				    {
					  PORTB |= Write_HIGH[i];
					  PORTC |= Write_HIGH[14];
					  PORTC |= Write_HIGH[15];
				    	_delay_ms(x);
				    }
				//turn off 8-11
				  for(int i = 8; i<12; i++)
			    {
			     PORTB |= Write_HIGH[i];
			      _delay_ms(x);
		  	    }
				//turn off 4-7
				for(int i=4;i<8;i++)
				{
			    	PORTD |= Write_HIGH[i];
					_delay_ms(x);
 	   			}
			   	//turn off 0-3
				for(int i=0;i<4;i++)
				{
		   		 PORTD |= Write_HIGH[i];
   			    	_delay_ms(x);
				}

			}
		}

		//up and down single layer stomp
		void layerstompUpAndDown(){
			int x=100;
			for(int i=0;i<4;i++)
			{
				PORTC &=~ Layer_LOW[i];
			}
			for(int y=0;y<5;y++)
			{
				for(int count =0;count<1;count++)
				{
					for(int i=0;i<4;i++)
					{
						PORTC |= Layer_HIGH[i];
						_delay_ms(x);
						PORTC &=~ Layer_LOW[i];
					}
					for(int i=4;i!=0;i--)
					{
						PORTC |= Layer_HIGH[i-1];
						_delay_ms(x);
						PORTC &=~ Layer_LOW[i-1];
					}
				}

				for(int i=0;i<4;i++)
				{
					PORTC |= Layer_HIGH[i];
					_delay_ms(x);
				}
				for(int i=4;i!=0;i--)
				{
					PORTC &=~ Layer_LOW[i-1];
					_delay_ms(x);
				}
			}
		}
		//flicker off
		void flickerOff(){
			turnEverythingOn();
			for(int i =0; i!=150;i+=5)
			{
				turnEverythingOff();
				_delay_ms(100);
				turnEverythingOn();
				_delay_ms(75);
			}
		}
		//around edge of the cube down
		void aroundEdgeDown(){
			int k=175;
			for(int x=200;x!=0;x-=50)
			{
				turnEverythingOff();
				for(int i=4;i!=0;i--)
				{
					PORTC |= Layer_HIGH[i-1];
				    PORTD &=~ Write_LOW[5];
					PORTD &=~ Write_LOW[6];
					PORTB &=~ Write_LOW[9];
					PORTB &=~ Write_LOW[10];
					PORTD &=~ Write_LOW[0];
					_delay_ms(k);
					PORTD |= Write_HIGH[0];
					PORTD &=~ Write_LOW[4];
					_delay_ms(k);
				  PORTD |=	Write_HIGH[4];
					PORTB &=~ Write_LOW[8];
					_delay_ms(k);
					PORTB |= Write_HIGH[8];
					PORTB &=~ Write_LOW[12];
					_delay_ms(k);
					PORTB |= Write_HIGH[12];
					PORTC &=~ Write_LOW[13];
					_delay_ms(k);
					PORTC |= Write_HIGH[13];
					PORTC &=~ Write_LOW[15];
					_delay_ms(k);
					PORTC |= Write_HIGH[14];
					PORTC &=~ Write_LOW[15];
					_delay_ms(k);
					PORTC |= Write_HIGH[14];
					PORTB &=~ Write_LOW[11];
					_delay_ms(k);
					PORTB |= Write_HIGH[11];
					PORTB &=~ Write_LOW[7];
					_delay_ms(k);
					PORTB |= Write_HIGH[7];
					PORTD &=~ Write_LOW[3];
					_delay_ms(k);
					PORTD |= Write_HIGH[3];
					PORTD &=~ Write_LOW[2];
					_delay_ms(k);
					PORTD |= Write_HIGH[2];
				PORTD &=~ Write_LOW[1];
					_delay_ms(k);
					PORTD |= Write_HIGH[1];
				}
			}
		}
		////diagonal rectangle
     void diagonalRectangle(){
    	 int x=350;
    	 turnEverythingOff();
    	 for(int count = 0; count<5; count++)
    	 {
    		 //top left
    		 for(int i=0;i<8;i++)
    		 {
    			 PORTD &=~ Write_LOW[i];
    		 }
    		 PORTC |= Layer_HIGH[3];
    		 PORTC |= Layer_HIGH[1];
    		 _delay_ms(x);
    		 turnEverythingOff();
    		 //middle middle
    		 for(int i = 4; i<8; i++)
    		 {
    			 PORTD &=~ Write_LOW[i];
    		 }
    		 for(int i = 8; i<12; i++)
    		 {
    			 PORTB &=~ Write_LOW[i];
    		 }
    		 for(int i = 1; i<3; i++)
    		 {
    			 PORTC |= Layer_HIGH[i];
    		 }
    		 _delay_ms(x);
    		 turnEverythingOff();
    		  //bottom right
    		     for(int i = 8; i<14; i++)
    		     {
    		    	 PORTB &=~ Write_LOW[i];
    		     }
    		     for(int i = 14; i<16; i++)
    		     {
    		    	 PORTC &=~ Write_LOW[i];
    		     }
    		     PORTC |= Layer_HIGH[0];
    		    PORTC |= Layer_HIGH[1];
    		    _delay_ms(x);
    		   turnEverythingOff();
    		   //bottom middle
    		       for(int i = 4; i<8; i++)
    		       {
    		    	   PORTD &=~ Write_LOW[i];
    		       }
    		       for(int i = 8; i<12; i++)
    		       {
    		         PORTB &=~ Write_LOW[i];
    		       }
    		       PORTC |= Layer_HIGH[0];
    		       PORTC |= Layer_HIGH[1];
    		       _delay_ms(x);
    		       turnEverythingOff();
    		       //bottom left
    		       for(int i = 0; i<8; i++)
    		        {
    		    	   PORTD &=~ Write_LOW[i];
    		        }
    		       PORTC |= Layer_HIGH[0];
    		       PORTC |= Layer_HIGH[1];
    		        _delay_ms(x);
    		      turnEverythingOff();

    		      //middle middle
    		      for(int i = 4; i<8; i++)
    		       {
    		         PORTD &=~ Write_LOW[i];
    		       }
    		      for(int i = 8; i<12; i++)
    		      {
    		          PORTB &=~ Write_LOW[i];
    		      }
    		      PORTC |= Layer_HIGH[1];
    		      PORTC |= Layer_HIGH[2];
    		      _delay_ms(x);
    		       turnEverythingOff();

    		       //top right
    		           for(int i = 8; i<14; i++)
    		           {
    		        	   PORTB &=~ Write_LOW[i];
    		           }
    		           for(int i = 14; i<16; i++)
    		           {
    		        	   PORTC &=~ Write_LOW[i];
    		           }
    		           PORTC |= Layer_HIGH[2];
    		           PORTC |= Layer_HIGH[3];
    		           _delay_ms(x);
    		           turnEverythingOff();
    		           //top middle
    		               for(int i = 4; i<8; i++)
    		               {
    		            	   PORTD &=~ Write_LOW[i];
    		               }
    		               for(int i = 8; i<12; i++)
    		               {
    		            	   PORTB &=~ Write_LOW[i];
    		               }
    		               PORTC |= Layer_HIGH[2];
    		              PORTC |= Layer_HIGH[3];
    		               _delay_ms(x);
    		              turnEverythingOff();
    	 }//optional if not working
    		              //top left
    		                for(int i = 0; i<8; i++)
    		                {
    		                	PORTD &=~ Write_LOW[i];
    		                }
    		                PORTC |= Layer_HIGH[3];
    		             PORTC |= Layer_HIGH[2];
    		                _delay_ms(x);
    		               turnEverythingOff();
    	// }//else
     }
     //propeller
     void propeller()
     {
    	 turnEverythingOff();
    	 int x=90;
    	 for(int y=4;y>0;y--)
    	 {
    		 for(int i=0;i<6;i++)
    		 {
    			 //turn on layer
    			 PORTC=Layer_HIGH[y-1];
    			 //a1
    			 turnColumnsOff();
    			 PORTD &=~ (1<<PD0);
    			 PORTD &=~ (1<<PD5);
    			 PORTB &=~ (1<<PB2);             // PORTB=Write_LOW[10];
    			 PORTC &=~ (1<<PC5);//A5 PORTC=Write_LOW[15];
    			 _delay_ms(x);

    			 //b1
    			 turnColumnsOff();
    			 PORTD &=~ (1<<PD4);//4 PORTD=Write_LOW[4];
    			 PORTD &=~ (1<<PD5);//5 PORTD=Write_LOW[5];
    			 PORTB &=~ (1<<PB2);//10 PORTB=Write_LOW[10];
    			 PORTB &=~ (1<<PB3);//11 PORTB=Write_LOW[11];
    			 _delay_ms(x);

    			 //c1
    			 turnColumnsOff();
    			 PORTD &=~ (1<<PD6);//6 PORTD=Write_LOW[6];
    			 PORTD &=~ (1<<PD7);//7 PORTD=Write_LOW[7];
    			 PORTB &=~ (1<<PB0);//8 PORTB=Write_LOW[8];
    			 PORTB &=~ (1<<PB1);//9 PORTB=Write_LOW[9];
    		    _delay_ms(x);

    		    //d1
    		    turnColumnsOff();
    		    PORTD &=~ (1<<PD3);//3 PORTD=Write_LOW[3];
    		    PORTD &=~ (1<<PD6);//6 PORTD=Write_LOW[6];
    		    PORTB &=~ (1<<PB1);//9 PORTB=Write_LOW[9];
    		    PORTB &=~ (1<<PB4);//12 PORTB=Write_LOW[12];
    		   _delay_ms(x);

    		   //d2
    		   turnColumnsOff();
    		   PORTD &=~ (1<<PD2);//2 PORTD=Write_LOW[2];
    		   PORTD &=~ (1<<PD6);//6 PORTD=Write_LOW[6];
			   PORTB &=~ (1<<PB1);//9 PORTB=Write_LOW[9];
			   PORTB &=~ (1<<PB5);//13 PORTB=Write_LOW[13];
    		   _delay_ms(x);

    		   //d3
    		   turnColumnsOff();
    		    PORTD &=~ (1<<PD1);//1 PORTD=Write_LOW[1];
    		    PORTD &=~ (1<<PD5);//5 PORTD=Write_LOW[5];
				PORTB &=~ (1<<PB2);//10 PORTB=Write_LOW[10];
				PORTC &=~ (1<<PC4);//A4 PORTC=Write_LOW[14];
    		    _delay_ms(x);
    		 }
    	 }
    		    //d4
    		    turnColumnsOff();
    		    PORTD &=~ (1<<PD0);//0 PORTD=Write_LOW[0];
    		    PORTD &=~ (1<<PD5);//5 PORTD=Write_LOW[5];
				PORTB &=~ (1<<PB2);//10 PORTB=Write_LOW[10];
				PORTC &=~ (1<<PC5);//A5 PORTC=Write_LOW[15];
    		    _delay_ms(x);
    		// }
    	// }
     }



	//last

int main(void)
     {
     	DDRD = 0xFF;
     	DDRC |= (1<<DDC5)|(1<<DDC4)|(1<<DDC3)|(1<<DDC2)|(1<<DDC1)|(1<<DDC0);
     	DDRB |= (1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
while(1){
	turnEverythingOff();//turn all off
	  flickerOn();
    turnEverythingOn();//turn all on
	  //_delay_ms(200);
	  turnOnAndOffAllByLayerUpAndDownNotTimed();
	 // _delay_ms(200);
	  layerstompUpAndDown();
	// _delay_ms(200);
	 turnOnAndOffAllByColumnSideways();
  //  _delay_ms(200);
	aroundEdgeDown();
	//  _delay_ms(200);
	  turnEverythingOff();
	//  randomflicker();
	//  randomRain();
	  diagonalRectangle();
	//_delay_ms(200);
	//  goThroughAllLedsOneAtATime();
	  propeller();
	//  _delay_ms(200);
  //  spiralInAndOut();
	  flickerOff();
	 //  _delay_ms(200);
	  turnEverythingOff();
	  _delay_ms(5000);
}
}

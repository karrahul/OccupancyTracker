
#define IR1 0
#define IR2 1
#define IROffset 3

float FirstIR, SecondIR;
int Stock=0;
int IR1State=0; int IR2State=0;
int Field = 40;
float IR1raw[]={0,0,0,0,0};
float IR2raw[]={0,0,0,0,0};
int arraysize=5;

void setup() {
   
  Serial.begin(9600);
  delay(1000);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

}

void loop()
{  

  for(int i = 0; i < arraysize; i++)
  {
         IR1raw[i] = analogRead(IR1);
  }
  delay(10);
  for(int i = 0; i < arraysize; i++)
  {
         IR2raw[i] = analogRead(IR2);
  }
  
   isort(IR1raw, arraysize);
   isort(IR2raw, arraysize);
   
   int midpoint = arraysize/2; 
      
         FirstIR=SharpValue(IR1raw[midpoint],IROffset);
         if(FirstIR<Field)
         FirstIR=1;
         else
         FirstIR=0;
         
         SecondIR=SharpValue(IR2raw[midpoint],IROffset);
         if(SecondIR<Field)
         SecondIR=1;
         else
         SecondIR=0;

//Start Stock counter algo here
     
  if(FirstIR==1)
  IR1State=1;
  if(SecondIR==1)
  IR2State=1;
  
  if((IR1State==1)&&(SecondIR==1))
  { Stock = Stock+1;
  IR1State =0;
  IR2State=0;
  //Serial.println("Stock is");
         Serial.println(Stock);
         //Serial.println("----------------------------");
         delay(2000);
  }
  if((IR2State==1)&&(FirstIR==1))
  { Stock = Stock-1;
  IR1State =0;
  IR2State=0;
//  Serial.println("Stock is");
         Serial.println(Stock);
         //Serial.println("----------------------------");
         delay(2000);
  }
  
   
        
}




float SharpValue( float x, float y)
{
  float ScaledValue=0;
  float Cutoff=0;
  Cutoff=1299.8*pow(y,-0.774);
  if (x > Cutoff)
   {return 0;}
   else 
   { ScaledValue = (9960.9*pow(x,-1.282))-y;
   return ScaledValue;
   }
}

void isort(float *a, float n)

{
  for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

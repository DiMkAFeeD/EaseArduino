int �;
� = 3;
void setup(){
    pinMode( 7, OUTPUT);
}
void loop(){
    if ( �==3 ){
        digitalWrite( 7, HIGH);
        delay(100);
        digitalWrite( 7, LOW);
        delay(100);
    }
}

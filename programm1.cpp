int à;
à = 3;
void setup(){
    pinMode( 7, OUTPUT);
}
void loop(){
    if ( à==3 ){
        digitalWrite( 7, HIGH);
        delay(100);
        digitalWrite( 7, LOW);
        delay(100);
    }
}

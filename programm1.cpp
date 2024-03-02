void setup(){
    pinMode( 7, OUTPUT);
}

void loop(){
    digitalWrite( 7, true );
    delay( 100 );
    digitalWrite( 7, false );
    delay( 100 );
}

#define светодиод 7
void setup(){
    pinMode( светодиод, OUTPUT);
}
void loop(){
    digitalWrite( светодиод, true );
    delay( 1000 );
    digitalWrite( светодиод, false );
    delay( 1000 );
}

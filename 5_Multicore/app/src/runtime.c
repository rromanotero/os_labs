#define MINIOS_APP __attribute__ ((section (".entry_point"))) int

int main( void );

MINIOS_APP c_runtime(){

    //Setup BSS
    //(missing)
    //...

    return main();
}

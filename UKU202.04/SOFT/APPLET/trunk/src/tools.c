/*****************************************************************************/
/* Tool Module :                                                             */
/* Several tools for the implementation :                                    */
/* com_gt  : get one char of serial if with timeout                          */
#define COM_GT      0
/* putchar : send character on serial interface via sendblk                  */
#define PUTCHAR     1
/* sendblk : send data on ser.if with RS485 2-Wire support if set up         */
#define SENDBLK     1
/* a2tobcd   : 2 digit bcd-value in ASCII notation in int                    */
#define A2TOBCD     0
/* sprl    : make a string out of long-value                                 */
#define SPRL        0
/*****************************************************************************/
/* Version B1.10 tool pool                                                   */
/*****************************************************************************/
/* History :                                                                 */
/* 19/11/98 jl first version at all                                          */
/* 13/09/99 jl DEFINES implemented                                           */
/*****************************************************************************/
#include <style.h>
#include <globals.h>
#include <io.h>
#include <kernel.h>

extern int OutBuf( void );

/* external variables ********************************************************/


#if COM_GT
/****************************************************************************/
/* Function : com_gt                                                        */
/* Parameter: toutval = timeout in ms                                       */
/*--------------------------------------------------------------------------*/
/* get one char of serial interface if possible                             */
/*--------------------------------------------------------------------------*/
/* Returncode : received char or -1 for timeout                             */
/****************************************************************************/
signed int com_gt( WORD toutval )
{
    WORD x;

    if( kbhit( ) )
    {
        return( getch( ) );
    }

    x = sticks;
    while( 1 )
    {
        if( kbhit( ) )
        {
            return( getch( ) );
        }
        else
        {
            nice( );
        }
        if( toutval && ( ( sticks - x ) > ( WORD ) toutval ) )
        {
            return( -1 );
        }
    }
}
#endif

#if SENDBLK
/****************************************************************************/
/* Function : sendblk                                                       */
/* Parameter: sb = buffer; len = length                                     */
/*--------------------------------------------------------------------------*/
/* send data on serial interface                                           */
/*--------------------------------------------------------------------------*/
/* Returncode : -                                                           */
/****************************************************************************/
void sendblk( BYTE * sb, WORD len )
{
    int    i;
    extern BYTE Setup[ ];

    if( ( Setup[ 16 ] & 0x03 ) == 3 )
    {
        /* t.m. RS485/2 */
        lio_tx( 1 );		/* transmitter on, enable output */
        for( i = 0; i < len; i++ )
            putch( sb[ i ] );

        while( OutBuf( ) || LIOObuf( ) ) /* wait for last character sent */
            nice( );

        lio_tx( 0 );		/* transmitter off, disable output */
        FlushIn( );
    }
    else
    {
        for( i = 0; i < len; i++ )
            putch( sb[ i ] );
    }
    return;
}
#endif

#if PUTCHAR
/****************************************************************************/
/* Function : putchar                                                       */
/* Parameter: BYTE c = character                                            */
/*--------------------------------------------------------------------------*/
/* send character on serial interface via sendblk                           */
/*--------------------------------------------------------------------------*/
/* Returncode : -                                                           */
/****************************************************************************/
void putchar( BYTE c )
{
    if( ( Setup[ 16 ] & 0x03 ) == 3)
    {
        /* t.m. RS485/2 */
        lio_tx( 1 );		/* transmitter on, enable output */
        putch( c );
        while( OutBuf( ) || LIOObuf( ) ) /* wait for len-1 character sent */
            nice( );
        lio_tx( 0 );		/* transmitter off, disable output */
        FlushIn( );
    }
    else
    {
        putch( c );
    }
}
#endif


#if A2TOBCD
a2tobcd( char * p )
{
    return( p[ 0 ] & 0xf ) * 16 + ( p[ 1 ] & 0xf );
}
#endif


#if SPRL
/*****************************************************************************/
/* function sprl :                                                           */
/* simulates something like a sprintf                                        */
/* prints an long value in a string                                          */
/* length of string is always 10                                             */
/*****************************************************************************/
/* Version 1.00                                                              */
/*****************************************************************************/
/* Parameter  : unsigned char *p = where to put string (len must be min. 10) */
/*              unsigned int val = interger-value for conversion             */
/*****************************************************************************/
/* Returncode : rc = unsigned chr *p = pointer to created string             */
/*****************************************************************************/
/* History :                                                                 */
/* 19/11/98 jl first version at all                                          */
/*****************************************************************************/
BYTE * sprl( BYTE *p, DWORD val )
{
    int i;

    for( i = 0; i < 10; i++ )
    {
        p[ 9 - i ] = '0' + lmod( val, 10 );
        val = longdiv( val, 10 );
    }
    p += 10;
    return p;
}
#endif

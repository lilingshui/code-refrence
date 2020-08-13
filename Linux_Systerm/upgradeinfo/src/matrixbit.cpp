#pragma implementation "matrixbit.hpp"
#include "matrixbit.hpp"

void MatrixBit::SetXYBits( int X, int Y )
{
  iXbits = X;
  iYbits = Y;

  iXchars = ( X + 7 ) / 8;
  ichars = iXchars * Y;

  matrix = ( unsigned char * ) malloc( ichars );
  if ( matrix == NULL ) {
    perror( "can not get memory" );
    exit( -1 );
  }

  isload = false;
  _filename = NULL;
  /*canvas = NULL;*/
}

MatrixBit::~MatrixBit()
{
  if ( matrix != NULL ) {
    free( matrix );
  }
  if ( !_filename ) {
    free( _filename );
  }
}

bool MatrixBit::SetFile( char * filename )
{

  if ( access( filename, R_OK ) ) {
    printf( "can not access %s\n", filename );
    return false;
  }

  if ( _filename ) {
    free( _filename );
  }

  _filename = ( char * ) malloc( strlen( filename ) + 1 );
  if ( _filename == NULL ) {
    perror( " can not get more memory!" );
    exit( -1 );
  }

  strcpy( _filename, filename );

  return true;
}

void MatrixBit::SetOffset( int offset )
{
  ioffset = offset * ichars;
  isload = false;
}

bool MatrixBit::GetMatrix( )
{
  FILE * fp;

  fp = fopen( _filename, "r" );
  if ( fp == NULL ) {
    printf( "%s can not be opened\n", _filename );
    return false;
  }

  fseek( fp, ioffset, SEEK_SET );
  if ( fread( matrix, 1, ichars, fp ) != ( unsigned int )ichars ) {
    printf( "can not get matrix" );
    isload = false;
  }
  else {
    isload = true;
  }

  fclose( fp );
  return isload;
}

bool MatrixBit::Draw( int x, int y, bool isBlack )
{

  if ( !canvas ) {
    return false;
  }

  if ( !isload && !GetMatrix() ) {
    printf( "can not get matrix from file \n" );
    return false;
  }

  for ( int i = 0; i < iYbits; i ++ ) {
    for ( int j = 0; j < iXchars; j ++ ) {

      int _x = x + j * 8 + 7;
      unsigned char tmp = matrix[i * iXchars  + j];

      for ( int k = 0; k < 8; k ++){
	if ( tmp & 0x01 ){
	    canvas->DrawBit( _x, y, !isBlack );
	}
	else {
	    canvas->DrawBit( _x, y, isBlack );
	}

	tmp >>= 1;
	_x --;
      }
    }

    y ++;
  }


  return true;
}


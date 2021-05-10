/*
Copyright 2021 Sergei Pogrebniak (The Elder Guard)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <locale>
#include <codecvt>

using std::use_facet;
using std::locale;
using std::codecvt;
using std::mbstate_t;
using std::char_traits;

namespace Unicoder
{
  template<typename HighSource , typename HighDestination , typename LowSource , typename LowDestination>
  HighDestination & ProcessObject ( const HighSource & _value )
  {
    const codecvt<LowSource , LowDestination , mbstate_t> & converter = use_facet<codecvt<LowSource , LowDestination , mbstate_t>> ( locale ( ) );

    HighDestination buffer = HighDestination ( _value.length ( ) , static_cast< LowDestination >( 0 ) );

    const LowSource * from;
    LowDestination * to;

    converter.out ( mbstate_t ( ) , &_value [ 0 ] , &_value [ _value.length ( ) ] , from ,
                    &buffer [ 0 ] , &buffer [ buffer.length ( ) ] , to );

    buffer.resize ( to - &buffer [ 0 ] );

    return buffer;
  }

  template<typename Source , typename Destination>
  Destination *& ProcessPointer ( const Source * _value )
  {
    const codecvt<Source , Destination , mbstate_t> & converter = use_facet<codecvt<Source , Destination , mbstate_t>> ( locale ( ) );

    size_t length = char_traits<Source>::length ( _value );

    Destination * buffer = new Destination [ length + 1 ];

    for ( size_t c = 0; c < length + 1; c++ )
    {
      buffer [ c ] = static_cast< Destination >( 0 );
    }

    const Source * from;
    Destination * to;

    converter.out ( mbstate_t ( ) , &_value [ 0 ] , &_value [ length ] , from ,
                    &buffer [ 0 ] , &buffer [ length ] , to );

    return buffer;
  }
}

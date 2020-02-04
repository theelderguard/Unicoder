/*
© 2019, Serge Page.

This license is hereby grants to any person who obtained a copy of this product or the product source files the next rights to:

- Use a compiled version of this product at no cost, without any restrictions, in non-commercial and commercial purposes
- Do reverse-engineering of this product in non-commercial purposes only
- Use source codes of this product at no cost but with the limitations - source codes available only for non-commercial, academic and / or scientific purposes
- Copy and distribute without any fee
- Copy of the original repository and / or create own derivative product for non-commercial,  academic and / or scientific purposes only
- Link the product source code with an another product source code which licensed under any of Dark Orb licenses or one of these licenses:
  - MIT License
  - Microsoft Public License
  - Beerware License
  - Academic Free License
  - WTFPL
  - Unlicense
  - Original BSD license
  - Modified BSD License
  - Simplified BSD License
  - Zero Clause BSD
- Link the product source code with an another product source code if between them no any patent collision

This license is require to:

- Keep the full license text without any changes
- The license text must be included once in a file called 'License' which placed in the root directory of the product and in all source files of the product

This license is deny to:

- Change license of the derivative product
- Use the product’s author name and name of any contributor of this product for advertising derivative software without legally certified permission
- Resell this product
- Use the product or the product source code for any purpose which refers to any government of any country

The product is an original source codes and original compiled files which made by the original author and provided only under the grants and restrictions of this license. All damages which can be happen after and while using the product will not be compensate.
*/

#pragma once

#include <locale>

using std::use_facet;
using std::locale;

#include <codecvt>

using std::codecvt;
using std::mbstate_t;
using std::char_traits;

namespace Unicoder {
  class UConverter {
    public:
    template<typename Source, typename SourceChar, typename Destination, typename DestinationChar>
    static Destination FConvert( const Source &_Value ) {
      const codecvt<SourceChar, DestinationChar, mbstate_t> &VConverter = use_facet<codecvt<SourceChar, DestinationChar, mbstate_t>>( locale() );

      Destination VConvertedResult( _Value.length(), static_cast< DestinationChar>(0) );

      mbstate_t VInitialState = mbstate_t();

      const SourceChar *VMid1;
      DestinationChar *VMid2;

      VConverter.out( VInitialState, &_Value [ 0 ], &_Value [ _Value.length() ], VMid1,
                                 &VConvertedResult [ 0 ], &VConvertedResult [ VConvertedResult.length() ], VMid2 );

      VConvertedResult.resize( VMid2 - &VConvertedResult [ 0 ] );

      return VConvertedResult;
    }

    template<typename SourceChar, typename DestinationChar>
    static DestinationChar *FConvertRaw( const SourceChar *_Value ) {
      const codecvt<SourceChar, DestinationChar, mbstate_t> &VConverter = use_facet<codecvt<SourceChar, DestinationChar, mbstate_t>>( locale() );

      uint64_t VValueLength = char_traits<SourceChar>::length( _Value );

      DestinationChar *VConvertedResult = new DestinationChar [ VValueLength ];
      DestinationChar VInitialChar = static_cast< DestinationChar >( 0 );

      for( uint64_t c = 0; c < VValueLength; c++ ) {
        VConvertedResult [ c ] = VInitialChar;
      }

      mbstate_t VInitialState = mbstate_t();

      const SourceChar *VMid1;
      DestinationChar *VMid2;

      VConverter.out( VInitialState, &_Value [ 0 ], &_Value [ VValueLength ], VMid1,
                      &VConvertedResult [ 0 ], &VConvertedResult [ VValueLength ], VMid2 );

      return VConvertedResult;
    }
  };
}

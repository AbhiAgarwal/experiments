// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Note: custom allocators are not supported on VC6, since that compiler
// had trouble finding the function zlib_base::do_init.

#ifndef CPPCMS_BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED
#define CPPCMS_BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <cassert>                            
#include <iosfwd>            // streamsize.                 
#include <memory>            // allocator, bad_alloc.
#include <new>          
#include <cppcms_boost/config.hpp>  // MSVC, STATIC_CONSTANT, DEDUCED_TYPENAME, DINKUM.
#include <cppcms_boost/detail/workaround.hpp>
#include <cppcms_boost/iostreams/constants.hpp>   // buffer size.
#include <cppcms_boost/iostreams/detail/config/auto_link.hpp>
#include <cppcms_boost/iostreams/detail/config/dyn_link.hpp>
#include <cppcms_boost/iostreams/detail/config/wide_streams.hpp>
#include <cppcms_boost/iostreams/detail/config/zlib.hpp>
#include <cppcms_boost/iostreams/detail/ios.hpp>  // failure, streamsize.
#include <cppcms_boost/iostreams/filter/symmetric.hpp>                
#include <cppcms_boost/iostreams/pipeline.hpp>                
#include <cppcms_boost/type_traits/is_same.hpp>

// Must come last.
#ifdef CPPCMS_BOOST_MSVC
# pragma warning(push)
# pragma warning(disable:4251 4231 4660)         // Dependencies not exported.
#endif
#include <cppcms_boost/config/abi_prefix.hpp>           

namespace cppcms_boost { namespace iostreams {

namespace zlib {
                    // Typedefs

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned long ulong;

// Prefix 'x' prevents symbols from being redefined when Z_PREFIX is defined
typedef void* (*xalloc_func)(void*, zlib::uint, zlib::uint);
typedef void (*xfree_func)(void*, void*);

                    // Compression levels

CPPCMS_BOOST_IOSTREAMS_DECL extern const int no_compression;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int best_speed;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int best_compression;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int default_compression;

                    // Compression methods

CPPCMS_BOOST_IOSTREAMS_DECL extern const int deflated;

                    // Compression strategies

CPPCMS_BOOST_IOSTREAMS_DECL extern const int default_strategy;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int filtered;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int huffman_only;

                    // Status codes

CPPCMS_BOOST_IOSTREAMS_DECL extern const int okay;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int stream_end;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int stream_error;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int version_error;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int data_error;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int mem_error;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int buf_error;

                    // Flush codes

CPPCMS_BOOST_IOSTREAMS_DECL extern const int finish;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int no_flush;
CPPCMS_BOOST_IOSTREAMS_DECL extern const int sync_flush;

                    // Code for current OS

//BOOST_IOSTREAMS_DECL extern const int os_code;

                    // Null pointer constant.

const int null                               = 0;

                    // Default values

const int default_window_bits                = 15;
const int default_mem_level                  = 8;
const bool default_crc                       = false;
const bool default_noheader                  = false;

} // End namespace zlib. 

//
// Class name: zlib_params.
// Description: Encapsulates the parameters passed to deflateInit2
//      and inflateInit2 to customize compression and decompression.
//
struct zlib_params {

    // Non-explicit constructor.
    zlib_params( int level           = zlib::default_compression,
                 int method          = zlib::deflated,
                 int window_bits     = zlib::default_window_bits, 
                 int mem_level       = zlib::default_mem_level, 
                 int strategy        = zlib::default_strategy,
                 bool noheader       = zlib::default_noheader,
                 bool calculate_crc  = zlib::default_crc )
        : level(level), method(method), window_bits(window_bits),
          mem_level(mem_level), strategy(strategy),  
          noheader(noheader), calculate_crc(calculate_crc)
        { }
    int level;
    int method;
    int window_bits;
    int mem_level;
    int strategy;
    bool noheader;
    bool calculate_crc;
};

//
// Class name: zlib_error.
// Description: Subclass of std::ios::failure thrown to indicate
//     zlib errors other than out-of-memory conditions.
//
class CPPCMS_BOOST_IOSTREAMS_DECL zlib_error : public CPPCMS_BOOST_IOSTREAMS_FAILURE {
public:
    explicit zlib_error(int error);
    int error() const { return error_; }
    static void check(int error);
private:
    int error_;
};

namespace detail {

template<typename Alloc>
struct zlib_allocator_traits {
#ifndef CPPCMS_BOOST_NO_STD_ALLOCATOR
    typedef typename Alloc::template rebind<char>::other type;
#else
    typedef std::allocator<char> type;
#endif
};

template< typename Alloc,
          typename Base = // VC6 workaround (C2516)
              CPPCMS_BOOST_DEDUCED_TYPENAME zlib_allocator_traits<Alloc>::type >
struct zlib_allocator : private Base {
private:
    typedef typename Base::size_type size_type;
public:
    CPPCMS_BOOST_STATIC_CONSTANT(bool, custom = 
        (!is_same<std::allocator<char>, Base>::value));
    typedef typename zlib_allocator_traits<Alloc>::type allocator_type;
    static void* allocate(void* self, zlib::uint items, zlib::uint size);
    static void deallocate(void* self, void* address);
};

class CPPCMS_BOOST_IOSTREAMS_DECL zlib_base { 
public:
    typedef char char_type;
protected:
    zlib_base();
    ~zlib_base();
    void* stream() { return stream_; }
    template<typename Alloc> 
    void init( const zlib_params& p, 
               bool compress,
               zlib_allocator<Alloc>& zalloc )
        {
            bool custom = zlib_allocator<Alloc>::custom;
            do_init( p, compress,
                     #if !CPPCMS_BOOST_WORKAROUND(CPPCMS_BOOST_MSVC, < 1300)
                         custom ? zlib_allocator<Alloc>::allocate : 0,
                         custom ? zlib_allocator<Alloc>::deallocate : 0,
                     #endif
                     &zalloc );
        }
    void before( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end );
    void after( const char*& src_begin, char*& dest_begin, 
                bool compress );
    int xdeflate(int flush);  // Prefix 'x' prevents symbols from being 
    int xinflate(int flush);  // redefined when Z_PREFIX is defined
    void reset(bool compress, bool realloc);
public:
    zlib::ulong crc() const { return crc_; }
    int total_in() const { return total_in_; }
    int total_out() const { return total_out_; }
private:
    void do_init( const zlib_params& p, bool compress, 
                  #if !CPPCMS_BOOST_WORKAROUND(CPPCMS_BOOST_MSVC, < 1300)
                      zlib::xalloc_func, 
                      zlib::xfree_func, 
                  #endif
                  void* derived );
    void*        stream_;         // Actual type: z_stream*.
    bool         calculate_crc_;
    zlib::ulong  crc_;
    int          total_in_;
    int          total_out_;
};

//
// Template name: zlib_compressor_impl
// Description: Model of C-Style Filte implementing compression by
//      delegating to the zlib function deflate.
//
template<typename Alloc = std::allocator<char> >
class zlib_compressor_impl : public zlib_base, public zlib_allocator<Alloc> { 
public: 
    zlib_compressor_impl(const zlib_params& = zlib::default_compression);
    ~zlib_compressor_impl();
    bool filter( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end, bool flush );
    void close();
};

//
// Template name: zlib_compressor
// Description: Model of C-Style Filte implementing decompression by
//      delegating to the zlib function inflate.
//
template<typename Alloc = std::allocator<char> >
class zlib_decompressor_impl : public zlib_base, public zlib_allocator<Alloc> {
public:
    zlib_decompressor_impl(const zlib_params&);
    zlib_decompressor_impl(int window_bits = zlib::default_window_bits);
    ~zlib_decompressor_impl();
    bool filter( const char*& begin_in, const char* end_in,
                 char*& begin_out, char* end_out, bool flush );
    void close();
};

} // End namespace detail.

//
// Template name: zlib_compressor
// Description: Model of InputFilter and OutputFilter implementing
//      compression using zlib.
//
template<typename Alloc = std::allocator<char> >
struct basic_zlib_compressor 
    : symmetric_filter<detail::zlib_compressor_impl<Alloc>, Alloc> 
{
private:
    typedef detail::zlib_compressor_impl<Alloc>         impl_type;
    typedef symmetric_filter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_zlib_compressor( const zlib_params& = zlib::default_compression, 
                           int buffer_size = default_device_buffer_size );
    zlib::ulong crc() { return this->filter().crc(); }
    int total_in() {  return this->filter().total_in(); }
};
CPPCMS_BOOST_IOSTREAMS_PIPABLE(basic_zlib_compressor, 1)

typedef basic_zlib_compressor<> zlib_compressor;

//
// Template name: zlib_decompressor
// Description: Model of InputFilter and OutputFilter implementing
//      decompression using zlib.
//
template<typename Alloc = std::allocator<char> >
struct basic_zlib_decompressor 
    : symmetric_filter<detail::zlib_decompressor_impl<Alloc>, Alloc> 
{
private:
    typedef detail::zlib_decompressor_impl<Alloc>       impl_type;
    typedef symmetric_filter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_zlib_decompressor( int window_bits = zlib::default_window_bits,
                             int buffer_size = default_device_buffer_size );
    basic_zlib_decompressor( const zlib_params& p,
                             int buffer_size = default_device_buffer_size );
    zlib::ulong crc() { return this->filter().crc(); }
    int total_out() {  return this->filter().total_out(); }
};
CPPCMS_BOOST_IOSTREAMS_PIPABLE(basic_zlib_decompressor, 1)

typedef basic_zlib_decompressor<> zlib_decompressor;

//----------------------------------------------------------------------------//

//------------------Implementation of zlib_allocator--------------------------//

namespace detail {

template<typename Alloc, typename Base>
void* zlib_allocator<Alloc, Base>::allocate
    (void* self, zlib::uint items, zlib::uint size)
{ 
    size_type len = items * size;
    char* ptr = 
        static_cast<allocator_type*>(self)->allocate
            (len + sizeof(size_type)
            #if CPPCMS_BOOST_WORKAROUND(CPPCMS_BOOST_DINKUMWARE_STDLIB, == 1)
                , (char*)0
            #endif
            );
    *reinterpret_cast<size_type*>(ptr) = len;
    return ptr + sizeof(size_type);
}

template<typename Alloc, typename Base>
void zlib_allocator<Alloc, Base>::deallocate(void* self, void* address)
{ 
    char* ptr = reinterpret_cast<char*>(address) - sizeof(size_type);
    size_type len = *reinterpret_cast<size_type*>(ptr) + sizeof(size_type);
    static_cast<allocator_type*>(self)->deallocate(ptr, len); 
}

//------------------Implementation of zlib_compressor_impl--------------------//

template<typename Alloc>
zlib_compressor_impl<Alloc>::zlib_compressor_impl(const zlib_params& p)
{ init(p, true, static_cast<zlib_allocator<Alloc>&>(*this)); }

template<typename Alloc>
zlib_compressor_impl<Alloc>::~zlib_compressor_impl()
{ reset(true, false); }

template<typename Alloc>
bool zlib_compressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = xdeflate(flush ? zlib::finish : zlib::no_flush);
    after(src_begin, dest_begin, true);
    zlib_error::check(result);
    return result != zlib::stream_end; 
}

template<typename Alloc>
void zlib_compressor_impl<Alloc>::close() { reset(true, true); }

//------------------Implementation of zlib_decompressor_impl------------------//

template<typename Alloc>
zlib_decompressor_impl<Alloc>::zlib_decompressor_impl(const zlib_params& p)
{ init(p, false, static_cast<zlib_allocator<Alloc>&>(*this)); }

template<typename Alloc>
zlib_decompressor_impl<Alloc>::~zlib_decompressor_impl()
{ reset(false, false); }

template<typename Alloc>
zlib_decompressor_impl<Alloc>::zlib_decompressor_impl(int window_bits)
{ 
    zlib_params p;
    p.window_bits = window_bits;
    init(p, false, static_cast<zlib_allocator<Alloc>&>(*this)); 
}

template<typename Alloc>
bool zlib_decompressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool /* flush */ )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = xinflate(zlib::sync_flush);
    after(src_begin, dest_begin, false);
    zlib_error::check(result);
    return result != zlib::stream_end;
}

template<typename Alloc>
void zlib_decompressor_impl<Alloc>::close() { reset(false, true); }

} // End namespace detail.

//------------------Implementation of zlib_decompressor-----------------------//

template<typename Alloc>
basic_zlib_compressor<Alloc>::basic_zlib_compressor
    (const zlib_params& p, int buffer_size) 
    : base_type(buffer_size, p) { }

//------------------Implementation of zlib_decompressor-----------------------//

template<typename Alloc>
basic_zlib_decompressor<Alloc>::basic_zlib_decompressor
    (int window_bits, int buffer_size) 
    : base_type(buffer_size, window_bits) { }

template<typename Alloc>
basic_zlib_decompressor<Alloc>::basic_zlib_decompressor
    (const zlib_params& p, int buffer_size) 
    : base_type(buffer_size, p) { }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <cppcms_boost/config/abi_suffix.hpp> // Pops abi_suffix.hpp pragmas.
#ifdef CPPCMS_BOOST_MSVC
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED
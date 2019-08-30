// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef DATA_PRIMITIVES_HXX
#define DATA_PRIMITIVES_HXX

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 4000000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

#include <xsd/cxx/xml/dom/serialization-header.hxx>
#include <xsd/cxx/tree/serialization.hxx>
#include <xsd/cxx/tree/serialization/byte.hxx>
#include <xsd/cxx/tree/serialization/unsigned-byte.hxx>
#include <xsd/cxx/tree/serialization/short.hxx>
#include <xsd/cxx/tree/serialization/unsigned-short.hxx>
#include <xsd/cxx/tree/serialization/int.hxx>
#include <xsd/cxx/tree/serialization/unsigned-int.hxx>
#include <xsd/cxx/tree/serialization/long.hxx>
#include <xsd/cxx/tree/serialization/unsigned-long.hxx>
#include <xsd/cxx/tree/serialization/boolean.hxx>
#include <xsd/cxx/tree/serialization/float.hxx>
#include <xsd/cxx/tree/serialization/double.hxx>
#include <xsd/cxx/tree/serialization/decimal.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type< char, type > simple_type;
  typedef ::xsd::cxx::tree::type container;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long integer;
  typedef long long non_positive_integer;
  typedef unsigned long long non_negative_integer;
  typedef unsigned long long positive_integer;
  typedef long long negative_integer;

  // Boolean.
  //
  typedef bool boolean;

  // Floating-point types.
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken > nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< char, ncname, type > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone time_zone;
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::gday< char, simple_type > gday;
  typedef ::xsd::cxx::tree::gmonth< char, simple_type > gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, simple_type > gmonth_day;
  typedef ::xsd::cxx::tree::gyear< char, simple_type > gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, simple_type > gyear_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  typedef ::xsd::cxx::tree::content_order content_order;
  // Namespace information and list stream. Used in
  // serialization functions.
  //
  typedef ::xsd::cxx::xml::dom::namespace_info< char > namespace_info;
  typedef ::xsd::cxx::xml::dom::namespace_infomap< char > namespace_infomap;
  typedef ::xsd::cxx::tree::list_stream< char > list_stream;
  typedef ::xsd::cxx::tree::as_double< double_ > as_double;
  typedef ::xsd::cxx::tree::as_decimal< decimal > as_decimal;
  typedef ::xsd::cxx::tree::facet facet;

  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::bounds< char > bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;
  typedef ::xsd::cxx::tree::no_type_info< char > no_type_info;
  typedef ::xsd::cxx::tree::not_derived< char > not_derived;
  typedef ::xsd::cxx::tree::serialization< char > serialization;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::auto_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
class AngleUnitEnumType;
class DataThingType;
class ForceUnitEnumType;
class FractionType;
class LengthUnitEnumType;
class PointType;
class PoseType;
class PositiveDecimalType;
class TorqueUnitEnumType;
class TwistType;
class VectorType;
class WrenchType;

#include <memory>    // ::std::auto_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

class AngleUnitEnumType: public ::xml_schema::nmtoken
{
  public:
  enum value
  {
    degree,
    radian
  };

  AngleUnitEnumType (value v);

  AngleUnitEnumType (const char* v);

  AngleUnitEnumType (const ::std::string& v);

  AngleUnitEnumType (const ::xml_schema::nmtoken& v);

  AngleUnitEnumType (const ::xercesc::DOMElement& e,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  AngleUnitEnumType (const ::xercesc::DOMAttr& a,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  AngleUnitEnumType (const ::std::string& s,
                     const ::xercesc::DOMElement* e,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  AngleUnitEnumType (const AngleUnitEnumType& x,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  virtual AngleUnitEnumType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  AngleUnitEnumType&
  operator= (value v);

  virtual
  operator value () const
  {
    return _xsd_AngleUnitEnumType_convert ();
  }

  protected:
  value
  _xsd_AngleUnitEnumType_convert () const;

  public:
  static const char* const _xsd_AngleUnitEnumType_literals_[2];
  static const value _xsd_AngleUnitEnumType_indexes_[2];
};

class DataThingType: public ::xml_schema::type
{
  public:
  // Name
  //
  typedef ::xml_schema::id Name_type;
  typedef ::xsd::cxx::tree::optional< Name_type > Name_optional;
  typedef ::xsd::cxx::tree::traits< Name_type, char > Name_traits;

  const Name_optional&
  Name () const;

  Name_optional&
  Name ();

  void
  Name (const Name_type& x);

  void
  Name (const Name_optional& x);

  void
  Name (::std::auto_ptr< Name_type > p);

  // Constructors.
  //
  DataThingType ();

  DataThingType (const ::xercesc::DOMElement& e,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  DataThingType (const DataThingType& x,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  virtual DataThingType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  DataThingType&
  operator= (const DataThingType& x);

  virtual 
  ~DataThingType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  Name_optional Name_;
};

class ForceUnitEnumType: public ::xml_schema::nmtoken
{
  public:
  enum value
  {
    newton,
    pound,
    ounce
  };

  ForceUnitEnumType (value v);

  ForceUnitEnumType (const char* v);

  ForceUnitEnumType (const ::std::string& v);

  ForceUnitEnumType (const ::xml_schema::nmtoken& v);

  ForceUnitEnumType (const ::xercesc::DOMElement& e,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  ForceUnitEnumType (const ::xercesc::DOMAttr& a,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  ForceUnitEnumType (const ::std::string& s,
                     const ::xercesc::DOMElement* e,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  ForceUnitEnumType (const ForceUnitEnumType& x,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  virtual ForceUnitEnumType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  ForceUnitEnumType&
  operator= (value v);

  virtual
  operator value () const
  {
    return _xsd_ForceUnitEnumType_convert ();
  }

  protected:
  value
  _xsd_ForceUnitEnumType_convert () const;

  public:
  static const char* const _xsd_ForceUnitEnumType_literals_[3];
  static const value _xsd_ForceUnitEnumType_indexes_[3];
};

class FractionType: public ::xsd::cxx::tree::fundamental_base< ::xml_schema::decimal, char, ::xml_schema::simple_type, ::xsd::cxx::tree::schema_type::decimal >
{
  public:
  // Constructors.
  //
  FractionType (const ::xml_schema::decimal&);

  FractionType (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  FractionType (const ::xercesc::DOMAttr& a,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  FractionType (const ::std::string& s,
                const ::xercesc::DOMElement* e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  FractionType (const FractionType& x,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  virtual FractionType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~FractionType ();
};

class LengthUnitEnumType: public ::xml_schema::nmtoken
{
  public:
  enum value
  {
    meter,
    millimeter,
    inch
  };

  LengthUnitEnumType (value v);

  LengthUnitEnumType (const char* v);

  LengthUnitEnumType (const ::std::string& v);

  LengthUnitEnumType (const ::xml_schema::nmtoken& v);

  LengthUnitEnumType (const ::xercesc::DOMElement& e,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

  LengthUnitEnumType (const ::xercesc::DOMAttr& a,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

  LengthUnitEnumType (const ::std::string& s,
                      const ::xercesc::DOMElement* e,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

  LengthUnitEnumType (const LengthUnitEnumType& x,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

  virtual LengthUnitEnumType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  LengthUnitEnumType&
  operator= (value v);

  virtual
  operator value () const
  {
    return _xsd_LengthUnitEnumType_convert ();
  }

  protected:
  value
  _xsd_LengthUnitEnumType_convert () const;

  public:
  static const char* const _xsd_LengthUnitEnumType_literals_[3];
  static const value _xsd_LengthUnitEnumType_indexes_[3];
};

class PointType: public ::DataThingType
{
  public:
  // X
  //
  typedef ::xml_schema::decimal X_type;
  typedef ::xsd::cxx::tree::traits< X_type, char, ::xsd::cxx::tree::schema_type::decimal > X_traits;

  const X_type&
  X () const;

  X_type&
  X ();

  void
  X (const X_type& x);

  // Y
  //
  typedef ::xml_schema::decimal Y_type;
  typedef ::xsd::cxx::tree::traits< Y_type, char, ::xsd::cxx::tree::schema_type::decimal > Y_traits;

  const Y_type&
  Y () const;

  Y_type&
  Y ();

  void
  Y (const Y_type& x);

  // Z
  //
  typedef ::xml_schema::decimal Z_type;
  typedef ::xsd::cxx::tree::traits< Z_type, char, ::xsd::cxx::tree::schema_type::decimal > Z_traits;

  const Z_type&
  Z () const;

  Z_type&
  Z ();

  void
  Z (const Z_type& x);

  // Constructors.
  //
  PointType (const X_type&,
             const Y_type&,
             const Z_type&);

  PointType (const ::xercesc::DOMElement& e,
             ::xml_schema::flags f = 0,
             ::xml_schema::container* c = 0);

  PointType (const PointType& x,
             ::xml_schema::flags f = 0,
             ::xml_schema::container* c = 0);

  virtual PointType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  PointType&
  operator= (const PointType& x);

  virtual 
  ~PointType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< X_type > X_;
  ::xsd::cxx::tree::one< Y_type > Y_;
  ::xsd::cxx::tree::one< Z_type > Z_;
};

class PoseType: public ::DataThingType
{
  public:
  // Point
  //
  typedef ::PointType Point_type;
  typedef ::xsd::cxx::tree::traits< Point_type, char > Point_traits;

  const Point_type&
  Point () const;

  Point_type&
  Point ();

  void
  Point (const Point_type& x);

  void
  Point (::std::auto_ptr< Point_type > p);

  // XAxis
  //
  typedef ::VectorType XAxis_type;
  typedef ::xsd::cxx::tree::traits< XAxis_type, char > XAxis_traits;

  const XAxis_type&
  XAxis () const;

  XAxis_type&
  XAxis ();

  void
  XAxis (const XAxis_type& x);

  void
  XAxis (::std::auto_ptr< XAxis_type > p);

  // ZAxis
  //
  typedef ::VectorType ZAxis_type;
  typedef ::xsd::cxx::tree::traits< ZAxis_type, char > ZAxis_traits;

  const ZAxis_type&
  ZAxis () const;

  ZAxis_type&
  ZAxis ();

  void
  ZAxis (const ZAxis_type& x);

  void
  ZAxis (::std::auto_ptr< ZAxis_type > p);

  // Constructors.
  //
  PoseType (const Point_type&,
            const XAxis_type&,
            const ZAxis_type&);

  PoseType (::std::auto_ptr< Point_type >,
            ::std::auto_ptr< XAxis_type >,
            ::std::auto_ptr< ZAxis_type >);

  PoseType (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  PoseType (const PoseType& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  virtual PoseType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  PoseType&
  operator= (const PoseType& x);

  virtual 
  ~PoseType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< Point_type > Point_;
  ::xsd::cxx::tree::one< XAxis_type > XAxis_;
  ::xsd::cxx::tree::one< ZAxis_type > ZAxis_;
};

class PositiveDecimalType: public ::xsd::cxx::tree::fundamental_base< ::xml_schema::decimal, char, ::xml_schema::simple_type, ::xsd::cxx::tree::schema_type::decimal >
{
  public:
  // Constructors.
  //
  PositiveDecimalType (const ::xml_schema::decimal&);

  PositiveDecimalType (const ::xercesc::DOMElement& e,
                       ::xml_schema::flags f = 0,
                       ::xml_schema::container* c = 0);

  PositiveDecimalType (const ::xercesc::DOMAttr& a,
                       ::xml_schema::flags f = 0,
                       ::xml_schema::container* c = 0);

  PositiveDecimalType (const ::std::string& s,
                       const ::xercesc::DOMElement* e,
                       ::xml_schema::flags f = 0,
                       ::xml_schema::container* c = 0);

  PositiveDecimalType (const PositiveDecimalType& x,
                       ::xml_schema::flags f = 0,
                       ::xml_schema::container* c = 0);

  virtual PositiveDecimalType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~PositiveDecimalType ();
};

class TorqueUnitEnumType: public ::xml_schema::nmtoken
{
  public:
  enum value
  {
    newtonMeter,
    footPound
  };

  TorqueUnitEnumType (value v);

  TorqueUnitEnumType (const char* v);

  TorqueUnitEnumType (const ::std::string& v);

  TorqueUnitEnumType (const ::xml_schema::nmtoken& v);

  TorqueUnitEnumType (const ::xercesc::DOMElement& e,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

  TorqueUnitEnumType (const ::xercesc::DOMAttr& a,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

  TorqueUnitEnumType (const ::std::string& s,
                      const ::xercesc::DOMElement* e,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

  TorqueUnitEnumType (const TorqueUnitEnumType& x,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

  virtual TorqueUnitEnumType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  TorqueUnitEnumType&
  operator= (value v);

  virtual
  operator value () const
  {
    return _xsd_TorqueUnitEnumType_convert ();
  }

  protected:
  value
  _xsd_TorqueUnitEnumType_convert () const;

  public:
  static const char* const _xsd_TorqueUnitEnumType_literals_[2];
  static const value _xsd_TorqueUnitEnumType_indexes_[2];
};

class TwistType: public ::DataThingType
{
  public:
  // LinearVelocity
  //
  typedef ::VectorType LinearVelocity_type;
  typedef ::xsd::cxx::tree::traits< LinearVelocity_type, char > LinearVelocity_traits;

  const LinearVelocity_type&
  LinearVelocity () const;

  LinearVelocity_type&
  LinearVelocity ();

  void
  LinearVelocity (const LinearVelocity_type& x);

  void
  LinearVelocity (::std::auto_ptr< LinearVelocity_type > p);

  // AngularVelocity
  //
  typedef ::VectorType AngularVelocity_type;
  typedef ::xsd::cxx::tree::traits< AngularVelocity_type, char > AngularVelocity_traits;

  const AngularVelocity_type&
  AngularVelocity () const;

  AngularVelocity_type&
  AngularVelocity ();

  void
  AngularVelocity (const AngularVelocity_type& x);

  void
  AngularVelocity (::std::auto_ptr< AngularVelocity_type > p);

  // Constructors.
  //
  TwistType (const LinearVelocity_type&,
             const AngularVelocity_type&);

  TwistType (::std::auto_ptr< LinearVelocity_type >,
             ::std::auto_ptr< AngularVelocity_type >);

  TwistType (const ::xercesc::DOMElement& e,
             ::xml_schema::flags f = 0,
             ::xml_schema::container* c = 0);

  TwistType (const TwistType& x,
             ::xml_schema::flags f = 0,
             ::xml_schema::container* c = 0);

  virtual TwistType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  TwistType&
  operator= (const TwistType& x);

  virtual 
  ~TwistType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< LinearVelocity_type > LinearVelocity_;
  ::xsd::cxx::tree::one< AngularVelocity_type > AngularVelocity_;
};

class VectorType: public ::DataThingType
{
  public:
  // I
  //
  typedef ::xml_schema::decimal I_type;
  typedef ::xsd::cxx::tree::traits< I_type, char, ::xsd::cxx::tree::schema_type::decimal > I_traits;

  const I_type&
  I () const;

  I_type&
  I ();

  void
  I (const I_type& x);

  // J
  //
  typedef ::xml_schema::decimal J_type;
  typedef ::xsd::cxx::tree::traits< J_type, char, ::xsd::cxx::tree::schema_type::decimal > J_traits;

  const J_type&
  J () const;

  J_type&
  J ();

  void
  J (const J_type& x);

  // K
  //
  typedef ::xml_schema::decimal K_type;
  typedef ::xsd::cxx::tree::traits< K_type, char, ::xsd::cxx::tree::schema_type::decimal > K_traits;

  const K_type&
  K () const;

  K_type&
  K ();

  void
  K (const K_type& x);

  // Constructors.
  //
  VectorType (const I_type&,
              const J_type&,
              const K_type&);

  VectorType (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  VectorType (const VectorType& x,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  virtual VectorType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  VectorType&
  operator= (const VectorType& x);

  virtual 
  ~VectorType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< I_type > I_;
  ::xsd::cxx::tree::one< J_type > J_;
  ::xsd::cxx::tree::one< K_type > K_;
};

class WrenchType: public ::DataThingType
{
  public:
  // Force
  //
  typedef ::VectorType Force_type;
  typedef ::xsd::cxx::tree::traits< Force_type, char > Force_traits;

  const Force_type&
  Force () const;

  Force_type&
  Force ();

  void
  Force (const Force_type& x);

  void
  Force (::std::auto_ptr< Force_type > p);

  // Moment
  //
  typedef ::VectorType Moment_type;
  typedef ::xsd::cxx::tree::traits< Moment_type, char > Moment_traits;

  const Moment_type&
  Moment () const;

  Moment_type&
  Moment ();

  void
  Moment (const Moment_type& x);

  void
  Moment (::std::auto_ptr< Moment_type > p);

  // Constructors.
  //
  WrenchType (const Force_type&,
              const Moment_type&);

  WrenchType (::std::auto_ptr< Force_type >,
              ::std::auto_ptr< Moment_type >);

  WrenchType (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  WrenchType (const WrenchType& x,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  virtual WrenchType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  WrenchType&
  operator= (const WrenchType& x);

  virtual 
  ~WrenchType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< Force_type > Force_;
  ::xsd::cxx::tree::one< Moment_type > Moment_;
};

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

void
operator<< (::xercesc::DOMElement&, const AngleUnitEnumType&);

void
operator<< (::xercesc::DOMAttr&, const AngleUnitEnumType&);

void
operator<< (::xml_schema::list_stream&,
            const AngleUnitEnumType&);

void
operator<< (::xercesc::DOMElement&, const DataThingType&);

void
operator<< (::xercesc::DOMElement&, const ForceUnitEnumType&);

void
operator<< (::xercesc::DOMAttr&, const ForceUnitEnumType&);

void
operator<< (::xml_schema::list_stream&,
            const ForceUnitEnumType&);

void
operator<< (::xercesc::DOMElement&, const FractionType&);

void
operator<< (::xercesc::DOMAttr&, const FractionType&);

void
operator<< (::xml_schema::list_stream&,
            const FractionType&);

void
operator<< (::xercesc::DOMElement&, const LengthUnitEnumType&);

void
operator<< (::xercesc::DOMAttr&, const LengthUnitEnumType&);

void
operator<< (::xml_schema::list_stream&,
            const LengthUnitEnumType&);

void
operator<< (::xercesc::DOMElement&, const PointType&);

void
operator<< (::xercesc::DOMElement&, const PoseType&);

void
operator<< (::xercesc::DOMElement&, const PositiveDecimalType&);

void
operator<< (::xercesc::DOMAttr&, const PositiveDecimalType&);

void
operator<< (::xml_schema::list_stream&,
            const PositiveDecimalType&);

void
operator<< (::xercesc::DOMElement&, const TorqueUnitEnumType&);

void
operator<< (::xercesc::DOMAttr&, const TorqueUnitEnumType&);

void
operator<< (::xml_schema::list_stream&,
            const TorqueUnitEnumType&);

void
operator<< (::xercesc::DOMElement&, const TwistType&);

void
operator<< (::xercesc::DOMElement&, const VectorType&);

void
operator<< (::xercesc::DOMElement&, const WrenchType&);

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // DATA_PRIMITIVES_HXX

// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_DATABASE_ODB_NO_KEYS_2_ODB_HXX
#define DOGEN_DATABASE_ODB_NO_KEYS_2_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20200UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2020000 // 2.2.0
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/pgsql/gregorian-traits.hxx>
#include <odb/boost/date-time/pgsql/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/pgsql/uuid-traits.hxx>
//
// End prologue.

#include "dogen/database/types/no_keys_2.hpp"

#include <memory>
#include <cstddef>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#ifdef BOOST_TR1_MEMORY_HPP_INCLUDED
#  include <odb/tr1/wrapper-traits.hxx>
#  include <odb/tr1/pointer-traits.hxx>
#endif
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/no-id-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // no_keys_2
  //
  template <>
  struct class_traits< ::dogen::database::no_keys_2 >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::dogen::database::no_keys_2 >
  {
    public:
    typedef ::dogen::database::no_keys_2 object_type;
    typedef ::boost::shared_ptr< ::dogen::database::no_keys_2 > pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef void id_type;

    static const bool auto_id = false;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_id_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_id_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb
{
  // no_keys_2
  //
  template <typename A>
  struct query_columns< ::dogen::database::no_keys_2, id_pgsql, A >
  {
    // prop_0
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        int,
        pgsql::id_integer >::query_type,
      pgsql::id_integer >
    prop_0_type_;

    static const prop_0_type_ prop_0;
  };

  template <typename A>
  const typename query_columns< ::dogen::database::no_keys_2, id_pgsql, A >::prop_0_type_
  query_columns< ::dogen::database::no_keys_2, id_pgsql, A >::
  prop_0 (A::table_name, "\"prop_0\"", 0);

  template <typename A>
  struct pointer_query_columns< ::dogen::database::no_keys_2, id_pgsql, A >:
    query_columns< ::dogen::database::no_keys_2, id_pgsql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >:
    public access::object_traits< ::dogen::database::no_keys_2 >
  {
    public:
    struct image_type
    {
      // prop_0_
      //
      int prop_0_value;
      bool prop_0_null;

      std::size_t version;
    };

    using object_traits<object_type>::id;

    static bool
    grow (image_type&, bool*);

    static void
    bind (pgsql::bind*,
          image_type&,
          pgsql::statement_kind);

    static bool
    init (image_type&, const object_type&, pgsql::statement_kind);

    static void
    init (object_type&, const image_type&, database*);

    typedef pgsql::no_id_object_statements<object_type> statements_type;

    typedef pgsql::query_base query_base_type;

    static const std::size_t column_count = 1UL;
    static const std::size_t id_column_count = 0UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const char persist_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    static bool
    create_schema (database&, unsigned short pass, bool drop);

    static const char persist_statement_name[];
    static const char query_statement_name[];
    static const char erase_query_statement_name[];

    static const unsigned int persist_statement_types[];

    public:
  };

  template <>
  class access::object_traits_impl< ::dogen::database::no_keys_2, id_common >:
    public access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >
  {
  };

  // no_keys_2
  //
}

#include "dogen/database/odb/no_keys_2-odb.ixx"

#include <odb/post.hxx>

#endif // DOGEN_DATABASE_ODB_NO_KEYS_2_ODB_HXX

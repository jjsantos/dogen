// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen/database/odb/no_keys_2-odb.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/pgsql/traits.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/pgsql/transaction.hxx>
#include <odb/pgsql/connection.hxx>
#include <odb/pgsql/statement.hxx>
#include <odb/pgsql/statement-cache.hxx>
#include <odb/pgsql/no-id-object-statements.hxx>
#include <odb/pgsql/container-statements.hxx>
#include <odb/pgsql/exceptions.hxx>
#include <odb/pgsql/no-id-object-result.hxx>

namespace odb
{
  // no_keys_2
  //

  const char access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  persist_statement_name[] = "dogen_database_no_keys_2_persist";

  const char access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  query_statement_name[] = "dogen_database_no_keys_2_query";

  const char access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  erase_query_statement_name[] = "dogen_database_no_keys_2_erase_query";

  const unsigned int access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  persist_statement_types[] =
  {
    pgsql::int4_oid
  };

  bool access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  grow (image_type& i, bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // prop_0_
    //
    t[0UL] = 0;

    return grew;
  }

  void access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  bind (pgsql::bind* b,
        image_type& i,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    std::size_t n (0);

    // prop_0_
    //
    b[n].type = pgsql::bind::integer;
    b[n].buffer = &i.prop_0_value;
    b[n].is_null = &i.prop_0_null;
    n++;
  }

  bool access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  init (image_type& i, const object_type& o, pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    bool grew (false);

    // prop_0_
    //
    {
      int const& v =
        o.prop_0 ();

      bool is_null (false);
      pgsql::value_traits<
          int,
          pgsql::id_integer >::set_image (
        i.prop_0_value, is_null, v);
      i.prop_0_null = is_null;
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  init (object_type& o, const image_type& i, database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // prop_0_
    //
    {
      int v;

      pgsql::value_traits<
          int,
          pgsql::id_integer >::set_value (
        v,
        i.prop_0_value,
        i.prop_0_null);

      o.prop_0 (v);
    }
  }

  const char access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::persist_statement[] =
  "INSERT INTO \"kitanda\".\"no_keys_2\" ("
  "\"prop_0\")"
  " VALUES ($1)";

  const char access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::query_statement[] =
  "SELECT "
  "\"kitanda\".\"no_keys_2\".\"prop_0\""
  " FROM \"kitanda\".\"no_keys_2\""
  " ";

  const char access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::erase_query_statement[] =
  "DELETE FROM \"kitanda\".\"no_keys_2\""
  " ";

  const char access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::table_name[] =
  "\"kitanda\".\"no_keys_2\"";

  void access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  persist (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              obj,
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    callback (db,
              obj,
              callback_event::post_persist);
  }

  result< access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::object_type >
  access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  query (database&, const query_base_type& q)
  {
    using namespace pgsql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        sts.connection (),
        query_statement_name,
        query_statement + q.clause (),
        q.parameter_types (),
        q.parameter_count (),
        q.parameters_binding (),
        imb));

    st->execute ();
    st->deallocate ();

    shared_ptr< odb::no_id_object_result_impl<object_type> > r (
      new (shared) pgsql::no_id_object_result_impl<object_type> (
        q, st, sts));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    q.init_parameters ();
    delete_statement st (
      conn,
      erase_query_statement_name,
      erase_query_statement + q.clause (),
      q.parameter_types (),
      q.parameter_count (),
      q.parameters_binding ());

    return st.execute ();
  }

  bool access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::
  create_schema (database& db, unsigned short pass, bool drop)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (pass);
    ODB_POTENTIALLY_UNUSED (drop);

    if (drop)
    {
      switch (pass)
      {
        case 1:
        {
          db.execute ("DROP TABLE IF EXISTS \"kitanda\".\"no_keys_2\" CASCADE");
          return false;
        }
      }
    }
    else
    {
      switch (pass)
      {
        case 1:
        {
          db.execute ("CREATE TABLE \"kitanda\".\"no_keys_2\" (\n"
                      "  \"prop_0\" INTEGER NOT NULL)");
          return false;
        }
      }
    }

    return false;
  }

  static const schema_catalog_entry
  schema_catalog_entry_dogen_database_no_keys_2_ (
    id_pgsql,
    "",
    &access::object_traits_impl< ::dogen::database::no_keys_2, id_pgsql >::create_schema);
}

#include <odb/post.hxx>

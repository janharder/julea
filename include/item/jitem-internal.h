/*
 * JULEA - Flexible storage framework
 * Copyright (C) 2010-2017 Michael Kuhn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file
 **/

#ifndef H_ITEM_ITEM_INTERNAL
#define H_ITEM_ITEM_INTERNAL

#include <glib.h>

#include <julea-internal.h>

#include <item/jitem.h>

#include <item/jcollection.h>

#include <jcredentials-internal.h>
#include <jsemantics.h>

#include <bson.h>

J_GNUC_INTERNAL JItem* j_item_new (JCollection*, gchar const*, JDistribution*);
J_GNUC_INTERNAL JItem* j_item_new_from_bson (JCollection*, bson_t const*);

J_GNUC_INTERNAL JCollection* j_item_get_collection (JItem*);
J_GNUC_INTERNAL JCredentials* j_item_get_credentials (JItem*);

J_GNUC_INTERNAL bson_t* j_item_serialize (JItem*, JSemantics*);
J_GNUC_INTERNAL void j_item_deserialize (JItem*, bson_t const*);

J_GNUC_INTERNAL bson_oid_t const* j_item_get_id (JItem*);

J_GNUC_INTERNAL gboolean j_item_create_exec (JList*, JSemantics*);
J_GNUC_INTERNAL gboolean j_item_delete_exec (JList*, JSemantics*);
J_GNUC_INTERNAL gboolean j_item_get_exec (JList*, JSemantics*);

J_GNUC_INTERNAL void j_item_set_modification_time (JItem*, gint64);
J_GNUC_INTERNAL void j_item_set_size (JItem*, guint64);

J_GNUC_INTERNAL gboolean j_item_read_exec (JList*, JSemantics*);
J_GNUC_INTERNAL gboolean j_item_write_exec (JList*, JSemantics*);

J_GNUC_INTERNAL gboolean j_item_get_status_exec (JList*, JSemantics*);

#endif
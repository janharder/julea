/*
 * Copyright (c) 2010-2011 Michael Kuhn
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * \file
 **/

#include <glib.h>

#include "jmongo-reply.h"

#include "jmongo.h"

/**
 * \defgroup JMongoReply MongoDB Reply
 *
 * @{
 **/

/*
 * See http://www.mongodb.org/display/DOCS/Mongo+Wire+Protocol.
 */

/**
 * A MongoDB reply.
 **/
#pragma pack(4)
struct JMongoReply
{
	JMongoHeader header;
	gint32 response_flags;
	gint64 cursor_id;
	gint32 starting_from;
	gint32 number_returned;
	gchar data[];
};
#pragma pack()

JMongoReply*
j_mongo_reply_new (JMongoHeader* header)
{
	JMongoReply* reply;
	gsize length;

	g_return_val_if_fail(header != NULL, NULL);

	length = GINT32_FROM_LE(header->message_length);

	reply = g_malloc(length);
	reply->header.message_length = header->message_length;
	reply->header.request_id = header->request_id;
	reply->header.response_to = header->response_to;
	reply->header.op_code = header->op_code;

	return reply;
}

void
j_mongo_reply_free (JMongoReply* reply)
{
	g_return_if_fail(reply != NULL);

	g_free(reply);
}

gpointer
j_mongo_reply_fields (JMongoReply* reply)
{
	g_return_val_if_fail(reply != NULL, NULL);

	return &(reply->response_flags);
}

gpointer
j_mongo_reply_data (JMongoReply* reply)
{
	g_return_val_if_fail(reply != NULL, NULL);

	return reply->data;
}

gsize
j_mongo_reply_length (JMongoReply* reply)
{
	g_return_val_if_fail(reply != NULL, 0);

	return GINT32_FROM_LE(reply->header.message_length);
}

gint32
j_mongo_reply_number (JMongoReply* reply)
{
	g_return_val_if_fail(reply != NULL, -1);

	return GINT32_FROM_LE(reply->number_returned);
}

/**
 * @}
 **/
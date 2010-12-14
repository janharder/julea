/*
 * Copyright (c) 2010 Michael Kuhn
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

#include <glib.h>

#include "semantics.h"

struct JSemantics
{
	gint consistency;
	gint persistency;
	gint concurrency;
	gint security;

	guint ref_count;
};

JSemantics*
j_semantics_new (void)
{
	JSemantics* semantics;

	semantics = g_new(JSemantics, 1);
	semantics->concurrency = J_SEMANTICS_CONCURRENCY_STRICT;
	semantics->consistency = J_SEMANTICS_CONSISTENCY_STRICT;
	semantics->persistency = J_SEMANTICS_PERSISTENCY_STRICT;
	semantics->security = J_SEMANTICS_SECURITY_STRICT;
	semantics->ref_count = 1;

	return semantics;
}

JSemantics*
j_semantics_ref (JSemantics* semantics)
{
	semantics->ref_count++;

	return semantics;
}

void
j_semantics_unref (JSemantics* semantics)
{
	semantics->ref_count--;

	if (semantics->ref_count == 0)
	{
		g_free(semantics);
	}
}

void
j_semantics_set (JSemantics* semantics, gint key, gint value)
{
	if (key == J_SEMANTICS_CONCURRENCY)
	{
		semantics->concurrency = value;
	}
	else if (key == J_SEMANTICS_CONSISTENCY)
	{
		semantics->consistency = value;
	}
	else if (key == J_SEMANTICS_PERSISTENCY)
	{
		semantics->persistency = value;
	}
	else if (key == J_SEMANTICS_SECURITY)
	{
		semantics->security = value;
	}
}

gint
j_semantics_get (JSemantics* semantics, gint key)
{
	if (key == J_SEMANTICS_CONCURRENCY)
	{
		return semantics->concurrency;
	}
	else if (key == J_SEMANTICS_CONSISTENCY)
	{
		return semantics->consistency;
	}
	else if (key == J_SEMANTICS_PERSISTENCY)
	{
		return semantics->persistency;
	}
	else if (key == J_SEMANTICS_SECURITY)
	{
		return semantics->security;
	}
}
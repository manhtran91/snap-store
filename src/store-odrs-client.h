/*
 * Copyright (C) 2019 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <gio/gio.h>

#include "store-odrs-review.h"

G_BEGIN_DECLS

G_DECLARE_FINAL_TYPE (StoreOdrsClient, store_odrs_client, STORE, ODRS_CLIENT, GObject)

StoreOdrsClient *store_odrs_client_new                (void);

void             store_odrs_client_get_reviews_async  (StoreOdrsClient *client, const gchar *app_id, const gchar *version, gint64 limit,
                                                       GCancellable *cancellable, GAsyncReadyCallback callback, gpointer callback_data);

GPtrArray       *store_odrs_client_get_reviews_finish (StoreOdrsClient *client, GAsyncResult *result, GError **error);

G_END_DECLS
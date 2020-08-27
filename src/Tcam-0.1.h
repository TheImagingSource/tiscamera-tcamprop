/*
 * Copyright 2020 The Imaging Source Europe GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TCAMPROP_0_1_H
#define TCAMPROP_0_1_H

#include <glib-object.h>

G_BEGIN_DECLS

#define TCAM_TYPE_PROP tcam_prop_get_type()

#ifdef G_DECLARE_INTERFACE

G_DECLARE_INTERFACE (TcamProp, tcam_prop, TCAM, PROP, GObject)

#else

#define TCAM_PROP(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TCAM_TYPE_PROP, TcamProp))
#define TCAM_IS_PROP(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TCAM_TYPE_PROP))
#define TCAM_PROP_GET_IFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), TCAM_TYPE_PROP, TcamPropInterface))

GType tcam_prop_get_type (void);

typedef struct _TcamProp TcamProp; /* dummy object */
typedef struct _TcamPropInterface TcamPropInterface;

#endif

struct _TcamPropInterface
{
    GTypeInterface parent_interface;

    GSList* (*get_tcam_property_names) (TcamProp* self);
    gchar* (*get_tcam_property_type) (TcamProp* self,
                                      const gchar* name);
    gboolean (*get_tcam_property) (TcamProp* self,
                                   const gchar* name,
                                   GValue* value,
                                   GValue* min,
                                   GValue* max,
                                   GValue* def,
                                   GValue* step,
                                   GValue* type,
                                   GValue* flags,
                                   GValue* category,
                                   GValue* group);

    GSList* (*get_tcam_menu_entries) (TcamProp* self,
                                      const char* menu_name);

    gboolean (*set_tcam_property) (TcamProp* self,
                                   const gchar* name,
                                   const GValue* value);
    GSList* (*get_tcam_device_serials) (TcamProp* self);
    GSList* (*get_tcam_device_serials_backend) (TcamProp* self);
    gboolean (*get_tcam_device_info) (TcamProp* self,
                                      const char* serial,
                                      char** name,
                                      char** identifier,
                                      char** connection_type);

};

G_END_DECLS

#endif /* TCAMPROP_0_1_H */

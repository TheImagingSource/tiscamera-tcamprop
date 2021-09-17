/*
 * Copyright 2021 The Imaging Source Europe GmbH
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

#ifndef TCAMPROP_1_0_IMPL_H
#define TCAMPROP_1_0_IMPL_H

#include "Tcam-1.0.h"

G_BEGIN_DECLS

GType   tcam_error_get_type(void);
GQuark  tcam_error_quark(void);

GType   tcam_property_visibility_get_type( void );
GType   tcam_property_intrepresentation_get_type( void );
GType   tcam_property_floatrepresentation_get_type( void );
GType   tcam_property_type_get_type( void );

const gchar*            tcam_prop_base_get_name( TcamPropBase* self );
const gchar*            tcam_prop_base_get_display_name( TcamPropBase* self );
const gchar*            tcam_prop_base_get_description( TcamPropBase* self );
const gchar*            tcam_prop_base_get_category( TcamPropBase* self );
TcamPropertyVisibility  tcam_prop_base_get_visibility( TcamPropBase* self );
TcamPropertyType        tcam_prop_base_get_prop_type( TcamPropBase* self );

gboolean        tcam_prop_base_is_available( TcamPropBase* self, GError** err );
gboolean        tcam_prop_base_is_locked( TcamPropBase* self, GError** err );

gboolean        tcam_prop_boolean_get_value( TcamPropBoolean* self, GError** err );
void            tcam_prop_boolean_set_value( TcamPropBoolean* self, gboolean value, GError** err );
gboolean        tcam_prop_boolean_get_default( TcamPropBoolean* self, GError** err );

gint64          tcam_prop_integer_get_value( TcamPropInteger* self, GError** err );
void            tcam_prop_integer_set_value( TcamPropInteger* self, gint64 value, GError** err );
void            tcam_prop_integer_get_range( TcamPropInteger* self, gint64* min_value, gint64* max_value, gint64* default_value, gint64* step_value, GError** err );
const gchar*    tcam_prop_integer_get_unit( TcamPropInteger* self );
TcamPropertyIntRepresentation    tcam_prop_integer_get_representation( TcamPropInteger* self );

gdouble         tcam_prop_float_get_value( TcamPropFloat* self, GError** err );
void            tcam_prop_float_set_value( TcamPropFloat* self, gdouble value, GError** err );
void            tcam_prop_float_get_range( TcamPropFloat* self, gdouble* min_value, gdouble* max_value, gdouble* default_value, gdouble* step_value, GError** err );
const gchar*    tcam_prop_float_get_unit( TcamPropFloat* self );
TcamPropertyFloatRepresentation    tcam_prop_float_get_representation( TcamPropFloat* self );

gchar*          tcam_prop_enumeration_get_value( TcamPropEnumeration* self, GError** err );
void            tcam_prop_enumeration_set_value( TcamPropEnumeration* self, const char* value, GError** err );
GSList*         tcam_prop_enumeration_get_enum_entries( TcamPropEnumeration* self, GError** err );
const gchar*    tcam_prop_enumeration_get_default( TcamPropEnumeration* self, GError** err );

void            tcam_prop_command_execute_command( TcamPropCommand* self, GError** err );

GSList*         tcam_prop_provider_get_tcam_property_names( TcamPropProvider* self, GError** err );
TcamPropBase*   tcam_prop_provider_get_tcam_property( TcamPropProvider* self, const char* name, GError** err );

G_END_DECLS

#endif /* TCAMPROP_1_0_IMPL_H */

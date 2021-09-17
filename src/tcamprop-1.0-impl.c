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

#include "tcamprop-1.0-impl.h"

 //---------------------------------
 // Enumerations

static const GEnumValue _tcam_error_values[] =
{
    { TCAM_ERROR_SUCCESS,                       "TCAM_ERROR_SUCCESS", "no-error" },
    { TCAM_ERROR_UNKNOWN,                       "TCAM_ERROR_UNKNOWN", "unknown-error" },
    { TCAM_ERROR_PROPERTY_NOT_IMPLEMENTED,      "TCAM_ERROR_PROPERTY_NOT_IMPLEMENTED", "property-not-found" },
    { TCAM_ERROR_PROPERTY_NOT_AVAILABLE,        "TCAM_ERROR_PROPERTY_NOT_AVAILABLE", "not-available" },
    { TCAM_ERROR_PROPERTY_NOT_WRITEABLE,        "TCAM_ERROR_PROPERTY_NOT_WRITEABLE", "not-write-able" },
    { TCAM_ERROR_PROPERTY_TYPE_INCOMPATIBLE,    "TCAM_ERROR_PROPERTY_TYPE_INCOMPATIBLE", "incompatible-type" },
    { TCAM_ERROR_PROPERTY_VALUE_OUT_OF_RANGE,   "TCAM_ERROR_PROPERTY_VALUE_OUT_OF_RANGE", "property-value-out-of-range" },
    { TCAM_ERROR_NO_DEVICE_OPEN,                "TCAM_ERROR_NO_DEVICE_OPEN", "no-device-opened" },
    { TCAM_ERROR_DEVICE_LOST,                   "TCAM_ERROR_DEVICE_LOST", "device-lost" },
    { TCAM_ERROR_PARAMETER_NULL,                "TCAM_ERROR_PARAMETER_NULL", "parameter-null" },
    { 0, NULL, NULL }
};

GType tcam_error_get_type( void )
{
    static GType type = 0;
    if( !type )
    {
        type = g_enum_register_static( "TcamError", _tcam_error_values );
    }
    return type;
}

GQuark tcam_error_quark( void )
{
    return g_quark_from_static_string( "tcam-error-quark" );
}

static const GEnumValue _tcamprop_property_visibility_values[] = {
     {TCAM_PROPERTY_VISIBILITY_BEGINNER,    "TCAM_VISIBILITY_BEGINNER", "beginner"},
     {TCAM_PROPERTY_VISIBILITY_EXPERT,      "TCAM_VISIBILITY_EXPERT", "expert"},
     {TCAM_PROPERTY_VISIBILITY_GURU,        "TCAM_VISIBILITY_GURU", "guru"},
     {TCAM_PROPERTY_VISIBILITY_INVISIBLE,   "TCAM_VISIBILITY_INVISIBLE", "invisible" },
     { 0, NULL, NULL }
};


GType tcam_property_visibility_get_type( void )
{
    static GType type = 0;
    if( !type )
    {
        type = g_enum_register_static( "TcamPropertyVisibility", _tcamprop_property_visibility_values );
    }
    return type;
}

static const GEnumValue _tcamprop_property_intrepresentation_values[] = {
    {TCAM_PROPERTY_INTREPRESENTATION_LINEAR, "TCAM_INTREPRESENTATION_LINEAR", "Linear"},
    {TCAM_PROPERTY_INTREPRESENTATION_LOGARITHMIC, "TCAM_INTREPRESENTATION_LOGARITHMIC", "Logarithmic"},
    {TCAM_PROPERTY_INTREPRESENTATION_PURENUMBER, "TCAM_INTREPRESENTATION_PURENUMBER", "PureNumber"},
    {TCAM_PROPERTY_INTREPRESENTATION_HEXNUMBER, "TCAM_INTREPRESENTATION_HEXNUMBER", "HexNumber" },
    { 0, NULL, NULL }
};


GType tcam_property_intrepresentation_get_type( void )
{
    static GType type = 0;
    if( !type )
    {
        type = g_enum_register_static( "TcamPropertyIntRepresentation", _tcamprop_property_intrepresentation_values );
    }
    return type;
}

static const GEnumValue _tcamprop_property_floatrepresentation_values[] = {
    {TCAM_PROPERTY_FLOATREPRESENTATION_LINEAR,      "TCAM_FLOATREPRESENTATION_LINEAR", "Linear"},
    {TCAM_PROPERTY_FLOATREPRESENTATION_LOGARITHMIC, "TCAM_FLOATREPRESENTATION_LOGARITHMIC", "Logarithmic"},
    {TCAM_PROPERTY_FLOATREPRESENTATION_PURENUMBER,  "TCAM_FLOATREPRESENTATION_PURENUMBER", "PureNumber"},
    { 0, NULL, NULL }
};


GType tcam_property_floatrepresentation_get_type( void )
{
    static GType type = 0;
    if( !type )
    {
        type = g_enum_register_static( "TcamPropertyFloatRepresentation", _tcamprop_property_floatrepresentation_values );
    }
    return type;
}

static const GEnumValue _tcam_property_type_values[] = {
    {TCAM_PROPERTY_TYPE_INTEGER   , "TCAM_PROPERTY_TYPE_INTEGER", "Integer"},
    {TCAM_PROPERTY_TYPE_FLOAT, "TCAM_PROPERTY_TYPE_FLOAT", "Float"},
    {TCAM_PROPERTY_TYPE_ENUMERATION  , "TCAM_PROPERTY_TYPE_ENUMERATION", "Enumeration"},
    {TCAM_PROPERTY_TYPE_BOOLEAN  , "TCAM_PROPERTY_TYPE_BOOLEAN", "Boolean"},
    {TCAM_PROPERTY_TYPE_COMMAND, "TCAM_PROPERTY_TYPE_COMMAND", "Command"},
    { 0, NULL, NULL}
};

GType tcam_property_type_get_type (void)
{
    static GType type = 0;
    if (!type)
    {
        type = g_enum_register_static ("TcamPropertyType", _tcam_property_type_values);
    }
    return type;
}

//-------------------------------------------
// Prop-Nodes:

G_DEFINE_INTERFACE( TcamPropBase, tcam_prop_base, G_TYPE_OBJECT )

static void tcam_prop_base_default_init( __attribute__ ((unused)) TcamPropBaseInterface* instance )
{

}

/**
 * tcam_prop_base_get_name:
 * @self: A #TcamPropBase
 *
 * Returns: (type utf8) (transfer none): The name of this property.
 */
const gchar* tcam_prop_base_get_name( TcamPropBase* self )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPBASE( self ), NULL );

    TcamPropBaseInterface* iface = TCAM_PROPBASE_GET_IFACE( self );
    if( iface->get_name )
    {
        return iface->get_name( self );
    }
    return NULL;
}

/**
 * tcam_prop_base_get_display_name:
 * @self: A #TcamPropBase
 *
 * Returns: (type utf8) (transfer none): Return the display name for this property.
 */
const gchar* tcam_prop_base_get_display_name( TcamPropBase* self )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPBASE( self ), NULL );

    TcamPropBaseInterface* iface = TCAM_PROPBASE_GET_IFACE( self );
    if( iface->get_display_name )
    {
        return iface->get_display_name( self );
    }
    return NULL;
}

/**
 * tcam_prop_base_get_description:
 * @self: A #TcamPropBase
 *
 * Returns: (type utf8) (transfer none): Return the description for this property.
 */
const gchar* tcam_prop_base_get_description( TcamPropBase* self )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPBASE( self ), NULL );

    TcamPropBaseInterface* iface = TCAM_PROPBASE_GET_IFACE( self );
    if( iface->get_description )
    {
        return iface->get_description( self );
    }
    return NULL;
}

/**
 * tcam_prop_base_get_category:
 * @self: A #TcamPropBase
 *
 * Returns: (type utf8) (transfer none): Return the category for this property.
 */
const gchar* tcam_prop_base_get_category( TcamPropBase* self )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPBASE( self ), NULL );

    TcamPropBaseInterface* iface = TCAM_PROPBASE_GET_IFACE( self );
    if( iface->get_category )
    {
        return iface->get_category( self );
    }
    return NULL;
}

/**
 * tcam_prop_base_get_visibility:
 * @self: A #TcamPropBase
 *
 * Returns: Return the #TcamPropertyVisibility for this property.
 */
TcamPropertyVisibility tcam_prop_base_get_visibility( TcamPropBase* self )
{
    g_return_val_if_fail( self != NULL, 0 );
    g_return_val_if_fail( TCAM_IS_PROPBASE( self ), 0 );

    TcamPropBaseInterface* iface = TCAM_PROPBASE_GET_IFACE( self );
    if( iface->get_visibility )
    {
        return iface->get_visibility( self );
    }
    return TCAM_PROPERTY_VISIBILITY_INVISIBLE;
}

/**
 * tcam_prop_base_get_prop_type:
 * @self: A #TcamPropBase
 *
 * Returns: Return the #TcamPropertyType for this property.
 */
TcamPropertyType tcam_prop_base_get_prop_type( TcamPropBase* self )
{
    g_return_val_if_fail( self != NULL, 0 );
    g_return_val_if_fail( TCAM_IS_PROPBASE( self ), 0 );

    TcamPropBaseInterface* iface = TCAM_PROPBASE_GET_IFACE( self );
    if( iface->get_prop_type )
    {
        return iface->get_prop_type( self );
    }
    return 0;
}

/**
 * tcam_prop_base_is_available:
 * @self: A #TcamPropBase
 * @err: return location for a GError, or NULL
 *
 * Returns: Return if the property is 'available'.
 */
gboolean        tcam_prop_base_is_available( TcamPropBase* self, GError** err )
{
    g_return_val_if_fail( self != NULL, FALSE );
    g_return_val_if_fail( TCAM_IS_PROPBASE( self ), FALSE );

    TcamPropBaseInterface* iface = TCAM_PROPBASE_GET_IFACE( self );
    if( iface->is_available )
    {
        return iface->is_available( self, err );
    }
    return FALSE;
}

/**
 * tcam_prop_base_is_locked:
 * @self: A #TcamPropBase
 * @err: return location for a GError, or NULL
 *
 * Returns: Return if the property is 'locked'.
 */
gboolean        tcam_prop_base_is_locked( TcamPropBase* self, GError** err )
{
    g_return_val_if_fail( self != NULL, FALSE );
    g_return_val_if_fail( TCAM_IS_PROPBASE( self ), FALSE );

    TcamPropBaseInterface* iface = TCAM_PROPBASE_GET_IFACE( self );
    if( iface->is_locked )
    {
        return iface->is_locked( self, err );
    }
    return FALSE;
}

G_DEFINE_INTERFACE( TcamPropBoolean, tcam_prop_boolean, TCAM_TYPE_PROPBASE )

static void tcam_prop_boolean_default_init( __attribute__ ((unused)) TcamPropBooleanInterface* instance )
{}

/**
 * tcam_prop_boolean_get_value:
 * @self: A #TcamPropBoolean
 * @err: return location for a GError, or NULL
 *
 * Returns: The current value of the property.
 */
gboolean tcam_prop_boolean_get_value( TcamPropBoolean* self, GError** err )
{
    g_return_val_if_fail( self != NULL, FALSE );
    g_return_val_if_fail( TCAM_IS_PROPBOOLEAN( self ), FALSE );

    TcamPropBooleanInterface* iface = TCAM_PROPBOOLEAN_GET_IFACE( self );
    if( iface->get_value )
    {
        return iface->get_value( self, err );
    }
    return FALSE;
}

/**
 * tcam_prop_boolean_set_value:
 * @self: A #TcamPropBoolean
 * @value: The new value to set
 * @err: return location for a GError, or NULL
 */
void tcam_prop_boolean_set_value( TcamPropBoolean* self, gboolean value, GError** err )
{
    g_return_if_fail( self != NULL );
    g_return_if_fail( TCAM_IS_PROPBOOLEAN( self ) );

    TcamPropBooleanInterface* iface = TCAM_PROPBOOLEAN_GET_IFACE( self );
    if( iface->set_value )
    {
        iface->set_value( self, value, err );
    }
}

/**
 * tcam_prop_boolean_get_default:
 * @self: A #TcamPropBoolean
 * @err: return location for a GError, or NULL
 * Returns: The default-value for this property.
 */
gboolean tcam_prop_boolean_get_default( TcamPropBoolean* self, GError** err )
{
    g_return_val_if_fail( self != NULL, FALSE );
    g_return_val_if_fail( TCAM_IS_PROPBOOLEAN( self ), FALSE );

    TcamPropBooleanInterface* iface = TCAM_PROPBOOLEAN_GET_IFACE( self );
    if( iface->get_default )
    {
        return iface->get_default( self, err );
    }
    return FALSE;
}

G_DEFINE_INTERFACE( TcamPropInteger, tcam_prop_integer, TCAM_TYPE_PROPBASE )

static void tcam_prop_integer_default_init( __attribute__ ((unused)) TcamPropIntegerInterface* instance )
{}

/**
 * tcam_prop_integer_get_value:
 * @self: A #TcamPropInteger
 * @err: return location for a GError, or NULL
 *
 * Returns: The current value of the property.
 */
gint64 tcam_prop_integer_get_value( TcamPropInteger* self, GError** err )
{
    g_return_val_if_fail( self != NULL, 0 );
    g_return_val_if_fail( TCAM_IS_PROPINTEGER( self ), 0 );

    TcamPropIntegerInterface* iface = TCAM_PROPINTEGER_GET_IFACE( self );
    if( iface->get_value )
    {
        return iface->get_value( self, err );
    }
    return 0;
}

/**
 * tcam_prop_integer_set_value:
 * @self: A #TcamPropInteger
 * @value: The new value to set
 * @err: return location for a GError, or NULL
 */
void tcam_prop_integer_set_value( TcamPropInteger* self, gint64 value, GError** err )
{
    g_return_if_fail( self != NULL );
    g_return_if_fail( TCAM_IS_PROPINTEGER( self ) );

    TcamPropIntegerInterface* iface = TCAM_PROPINTEGER_GET_IFACE( self );
    if( iface->set_value )
    {
        iface->set_value( self, value, err );
    }
}

/**
 * tcam_prop_integer_get_range:
 * @self: A #TcamPropInteger
 * @min_value: (out) (optional): The minimum for this property.
 * @max_value: (out) (optional): The maximum for this property.
 * @default_value: (out) (optional): The default for this property.
 * @step_value: (out) (optional): The step delta for this property.
 * @err: return location for a GError, or NULL
 */
void tcam_prop_integer_get_range( TcamPropInteger* self, gint64* min_value, gint64* max_value, gint64* default_value, gint64* step_value, GError** err )
{
    g_return_if_fail( self != NULL );
    g_return_if_fail( TCAM_IS_PROPINTEGER( self ) );

    TcamPropIntegerInterface* iface = TCAM_PROPINTEGER_GET_IFACE( self );
    if( iface->get_range )
    {
        iface->get_range( self, min_value, max_value, default_value, step_value, err );
    }
}

/**
 * tcam_prop_integer_get_unit:
 * @self: A #TcamPropInteger
 * Returns: (transfer none) (nullable) (type utf8): The unit of this property or NULL if this property does not have a unit.
 */
const gchar* tcam_prop_integer_get_unit( TcamPropInteger* self )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPINTEGER( self ), NULL );

    TcamPropIntegerInterface* iface = TCAM_PROPINTEGER_GET_IFACE( self );
    if( iface->get_unit )
    {
        return iface->get_unit( self );
    }
    return NULL;
}

/**
 * tcam_prop_integer_get_representation:
 * @self: A #TcamPropInteger
 * Returns: The #TcamPropertyIntRepresentation of this property.
 */
TcamPropertyIntRepresentation tcam_prop_integer_get_representation( TcamPropInteger* self )
{
    g_return_val_if_fail( self != NULL, TCAM_PROPERTY_INTREPRESENTATION_LINEAR );
    g_return_val_if_fail( TCAM_IS_PROPINTEGER( self ), TCAM_PROPERTY_INTREPRESENTATION_LINEAR );

    TcamPropIntegerInterface* iface = TCAM_PROPINTEGER_GET_IFACE( self );
    if( iface->get_representation )
    {
        return iface->get_representation( self );
    }
    return TCAM_PROPERTY_INTREPRESENTATION_LINEAR;
}


G_DEFINE_INTERFACE( TcamPropFloat, tcam_prop_float, TCAM_TYPE_PROPBASE )

static void tcam_prop_float_default_init( __attribute__ ((unused)) TcamPropFloatInterface* instance )
{}

/**
 * tcam_prop_float_get_value:
 * @self: A #TcamPropFloat
 * @err: return location for a GError, or NULL
 *
 * Returns: The current value of the property.
 */
gdouble tcam_prop_float_get_value( TcamPropFloat* self, GError** err )
{
    g_return_val_if_fail( self != NULL, 0 );
    g_return_val_if_fail( TCAM_IS_PROPFLOAT( self ), 0 );

    TcamPropFloatInterface* iface = TCAM_PROPFLOAT_GET_IFACE( self );
    if( iface->get_value )
    {
        return iface->get_value( self, err );
    }
    return 0;
}

/**
 * tcam_prop_float_set_value:
 * @self: A #TcamPropFloat
 * @value: The new value to set
 * @err: return location for a GError, or NULL
 */
void tcam_prop_float_set_value( TcamPropFloat* self, gdouble value, GError** err )
{
    g_return_if_fail( self != NULL );
    g_return_if_fail( TCAM_IS_PROPFLOAT( self ) );

    TcamPropFloatInterface* iface = TCAM_PROPFLOAT_GET_IFACE( self );
    if( iface->set_value )
    {
        iface->set_value( self, value, err );
    }
}

/**
 * tcam_prop_float_get_range:
 * @self: A #TcamPropFloat
 * @min_value: (out) (optional): The minimum for this property.
 * @max_value: (out) (optional): The maximum for this property.
 * @default_value: (out) (optional): The default for this property.
 * @step_value: (out) (optional): The step delta for this property.
 * @err: return location for a GError, or NULL
 */
void tcam_prop_float_get_range( TcamPropFloat* self, gdouble* min_value, gdouble* max_value, gdouble* default_value, gdouble* step_value, GError** err )
{
    g_return_if_fail( self != NULL );
    g_return_if_fail( TCAM_IS_PROPFLOAT( self ) );

    TcamPropFloatInterface* iface = TCAM_PROPFLOAT_GET_IFACE( self );
    if( iface->get_range )
    {
        iface->get_range( self, min_value, max_value, default_value, step_value, err );
    }
}

/**
 * tcam_prop_float_get_unit:
 * @self: A #TcamPropFloat
 * Returns: (transfer none) (nullable) (type utf8): The unit of this property or NULL if this property does not have a unit.
 */
const gchar* tcam_prop_float_get_unit( TcamPropFloat* self )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPFLOAT( self ), NULL );

    TcamPropFloatInterface* iface = TCAM_PROPFLOAT_GET_IFACE( self );
    if( iface->get_unit )
    {
        return iface->get_unit( self );
    }
    return NULL;
}

/**
 * tcam_prop_float_get_representation:
 * @self: A #TcamPropFloat
 * Returns: The #TcamPropertyFloatRepresentation of this property.
 */
TcamPropertyFloatRepresentation tcam_prop_float_get_representation( TcamPropFloat* self )
{
    g_return_val_if_fail( self != NULL, TCAM_PROPERTY_FLOATREPRESENTATION_LINEAR );
    g_return_val_if_fail( TCAM_IS_PROPFLOAT( self ), TCAM_PROPERTY_FLOATREPRESENTATION_LINEAR );

    TcamPropFloatInterface* iface = TCAM_PROPFLOAT_GET_IFACE( self );
    if( iface->get_representation )
    {
        return iface->get_representation( self );
    }
    return TCAM_PROPERTY_FLOATREPRESENTATION_LINEAR;
}

G_DEFINE_INTERFACE( TcamPropEnumeration, tcam_prop_enumeration, TCAM_TYPE_PROPBASE )

static void tcam_prop_enumeration_default_init( __attribute__ ((unused)) TcamPropEnumerationInterface* instance )
{}

/**
 * tcam_prop_enumeration_get_value:
 * @self: A #TcamPropEnumeration
 * @err: return location for a GError, or NULL
 * Returns: (transfer full)(type utf8): The current value of the property
 */
char* tcam_prop_enumeration_get_value( TcamPropEnumeration* self, GError** err )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPENUMERATION( self ), NULL );

    TcamPropEnumerationInterface* iface = TCAM_PROPENUMERATION_GET_IFACE( self );
    if( iface->get_value )
    {
        return iface->get_value( self, err );
    }
    return NULL;
}

/**
 * tcam_prop_enumeration_set_value:
 * @self: A #TcamPropEnumeration
 * @value: (in) (not nullable): The new value to set
 * @err: return location for a GError, or NULL
 */
void tcam_prop_enumeration_set_value( TcamPropEnumeration* self, const char* value, GError** err )
{
    g_return_if_fail( self != NULL );
    g_return_if_fail( TCAM_IS_PROPENUMERATION( self ) );

    TcamPropEnumerationInterface* iface = TCAM_PROPENUMERATION_GET_IFACE( self );
    if( iface->set_value )
    {
        iface->set_value( self, value, err );
    }
}

/**
 * tcam_prop_enumeration_get_enum_entries:
 * @self: A #TcamPropEnumeration
 * @err: return location for a GError, or NULL
 * Returns: (transfer full)(element-type utf8): The list of enum entries.
 */
GSList* tcam_prop_enumeration_get_enum_entries( TcamPropEnumeration* self, GError** err )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPENUMERATION( self ), NULL );

    TcamPropEnumerationInterface* iface = TCAM_PROPENUMERATION_GET_IFACE( self );
    if( iface->get_enum_entries )
    {
        return iface->get_enum_entries( self, err );
    }
    return NULL;
}

/**
 * tcam_prop_enumeration_get_default:
 * @self: A #TcamPropEnumeration
 * @err: return location for a GError, or NULL
 * Returns: (transfer none)(type utf8): The default value of the property
 */
const gchar* tcam_prop_enumeration_get_default( TcamPropEnumeration* self, GError** err )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPENUMERATION( self ), NULL );

    TcamPropEnumerationInterface* iface = TCAM_PROPENUMERATION_GET_IFACE( self );
    if( iface->get_default )
    {
        return iface->get_default( self, err );
    }
    return NULL;
}

G_DEFINE_INTERFACE( TcamPropCommand, tcam_prop_command, TCAM_TYPE_PROPBASE )

static void tcam_prop_command_default_init( __attribute__ ((unused)) TcamPropCommandInterface* instance )
{}

/**
 * tcam_prop_command_execute_command:
 * @self: A #TcamPropCommand
 * @err: return location for a GError, or NULL
 */
void tcam_prop_command_execute_command( TcamPropCommand* self, GError** err )
{
    g_return_if_fail( self != NULL );
    g_return_if_fail( TCAM_IS_PROPCOMMAND( self ) );

    TcamPropCommandInterface* iface = TCAM_PROPCOMMAND_GET_IFACE( self );
    if( iface->execute_command )
    {
        iface->execute_command( self, err );
    }
}

G_DEFINE_INTERFACE( TcamPropProvider, tcam_prop_provider, G_TYPE_OBJECT )

static void tcam_prop_provider_default_init( __attribute__( (unused) )TcamPropProviderInterface* klass )
{}

/**
 * tcam_prop_provider_get_tcam_property_names:
 * @self: a #TcamPropProvider
 * @err: return location for a GError, or NULL
 *
 * Returns: (transfer full) (element-type utf8): Return a list of the available property names
 */
GSList* tcam_prop_provider_get_tcam_property_names( TcamPropProvider* self, GError** err )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPPROVIDER( self ), NULL );

    TcamPropProviderInterface* iface = TCAM_PROPPROVIDER_GET_IFACE( self );
    if( iface->get_tcam_property_names )
    {
        return iface->get_tcam_property_names( self, err );
    }
    return NULL;
}

/**
 * tcam_prop_provider_get_tcam_property:
 * @self: a #TcamPropProvider
 * @name: (not nullable): name of the property to find
 * @err: return location for a GError, or NULL
 *
 * Returns: (transfer full): Returns  a #GOject implementing #TcamPropBase representing the property or NULL on error
 */
TcamPropBase* tcam_prop_provider_get_tcam_property( TcamPropProvider* self, const char* name, GError** err )
{
    g_return_val_if_fail( self != NULL, NULL );
    g_return_val_if_fail( name != NULL, NULL );
    g_return_val_if_fail( TCAM_IS_PROPPROVIDER( self ), NULL );

    TcamPropProviderInterface* iface = TCAM_PROPPROVIDER_GET_IFACE( self );
    if( iface->get_tcam_property )
    {
        return iface->get_tcam_property( self, name, err );
    }
    return NULL;
}

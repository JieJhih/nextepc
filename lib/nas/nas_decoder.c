#define TRACE_MODULE _nasdec

#include "core_debug.h"
#include "nas_message.h"

c_int32_t nas_decode_attach_request(nas_message_t *message, pkbuf_t *pkbuf)
{
    nas_attach_request_t *attach_request = &message->emm.attach_request;
    c_uint16_t decoded = 0;
    c_int32_t size = 0;

    size = nas_decode_attach_type(&attach_request->attach_type, pkbuf);
    d_assert(size >= 0, return -1, "decode failed");
    decoded += size;

    size = nas_decode_eps_mobile_identity(
            &attach_request->eps_mobile_identity, pkbuf);
    d_assert(size >= 0, return -1, "decode failed");
    decoded += size;

    size = nas_decode_ue_network_capability(
            &attach_request->ue_network_capability, pkbuf);
    d_assert(size >= 0, return -1, "decode failed");
    decoded += size;

    size = nas_decode_esm_message_container(
            &attach_request->esm_message_container, pkbuf);
    d_assert(size >= 0, return -1, "decode failed");
    decoded += size;

    while(pkbuf->len > 0) 
    {
        c_uint8_t *buffer = pkbuf->payload;
        c_uint8_t type = (*buffer) >= 0x80 ? ((*buffer) & 0xf0) : (*buffer);

        size = sizeof(c_uint8_t);
        d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, return -1, 
                "pkbuf_header error");
        decoded += size;

        switch(type)
        {
            case NAS_ATTACH_REQUEST_OLD_P_TMSI_SIGNATURE_TYPE:
                size = nas_decode_p_tmsi_signature(
                        &attach_request->old_p_tmsi_signature, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_OLD_P_TMSI_SIGNATURE_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_ADDITIONAL_GUTI_TYPE:
                size = nas_decode_eps_mobile_identity(
                        &attach_request->additional_guti, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_ADDITIONAL_GUTI_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_LAST_VISITED_REGISTERED_TAI_TYPE:
                size = nas_decode_tracking_area_identity(
                        &attach_request->last_visited_registered_tai, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_LAST_VISITED_REGISTERED_TAI_TYPE;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_DRX_PARAMETER_TYPE:
                size = nas_decode_drx_parameter(
                        &attach_request->drx_parameter, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_DRX_PARAMETER_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_MS_NETWORK_CAPABILITY_TYPE:
                size = nas_decode_ms_network_capability(
                        &attach_request->ms_network_capability, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_MS_NETWORK_FEATURE_SUPPORT_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_OLD_LOCATION_AREA_IDENTIFICATION_TYPE:
                size = nas_decode_location_area_identification(
                        &attach_request->old_location_area_identification, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_OLD_LOCATION_AREA_IDENTIFICATION_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_TMSI_STATUS_TYPE:
                size = nas_decode_tmsi_status(
                        &attach_request->tmsi_status, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_TMSI_STATUS_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_MOBILE_STATION_CLASSMARK_2_TYPE:
                size = nas_decode_mobile_station_classmark_2(
                        &attach_request->mobile_station_classmark_2, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_MOBILE_STATION_CLASSMARK_2_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_MOBILE_STATION_CLASSMARK_3_TYPE:
                size = nas_decode_mobile_station_classmark_3(
                        &attach_request->mobile_station_classmark_3, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_MOBILE_STATION_CLASSMARK_3_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_SUPPORTED_CODECS_TYPE:
                size = nas_decode_supported_codec_list(
                        &attach_request->supported_codecs, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_SUPPORTED_CODECS_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_ADDITIONAL_UPDATE_TYPE_TYPE:
                size = nas_decode_additional_update_type(
                        &attach_request->additional_update_type, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_ADDITIONAL_UPDATE_TYPE_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_VOICE_DOMAIN_PREFERENCE_AND_UE_USAGE_SETTING_TYPE:
                size = nas_decode_voice_domain_preference_and_ue_usage_setting(
                        &attach_request->voice_domain_preference_and_ue_usage_setting, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_VOICE_DOMAIN_PREFERENCE_AND_UE_USAGE_SETTING_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_DEVICE_PROPERTIES_TYPE:
                size = nas_decode_device_properties(
                        &attach_request->device_properties, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_DEVICE_PROPERTIES_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_OLD_GUTI_TYPE_TYPE:
                size = nas_decode_guti_type(
                        &attach_request->old_guti_type, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_OLD_GUTI_TYPE_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_MS_NETWORK_FEATURE_SUPPORT_TYPE:
                size = nas_decode_ms_network_feature_support(
                        &attach_request->ms_network_feature_support, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_MS_NETWORK_FEATURE_SUPPORT_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_TMSI_BASED_NRI_CONTAINER_TYPE:
                size = nas_decode_network_resource_identifier_container(
                        &attach_request->tmsi_based_nri_container, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_TMSI_BASED_NRI_CONTAINER_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_T3324_VALUE_TYPE:
                size = nas_decode_gprs_timer_2(
                        &attach_request->t3324_value, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_T3324_VALUE_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_T3412_EXTENDED_VALUE_TYPE:
                size = nas_decode_gprs_timer_3(
                        &attach_request->t3412_extended_value, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_T3412_EXTENDED_VALUE_PRESENT;
                decoded += size;
                break;
            case NAS_ATTACH_REQUEST_EXTENDED_DRX_PARAMETERS_TYPE:
                size = nas_decode_extended_drx_parameters(
                        &attach_request->extended_drx_parameters, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                attach_request->presencemask |=
                    NAS_ATTACH_REQUEST_EXTENDED_DRX_PARAMETERS_PRESENT;
                decoded += size;
                break;
            default:
                d_error("Unknown type(0x%x) or not implemented\n", type);
                return -1;
        }

    }

    return decoded;
}

c_int32_t nas_decode_attach_complete(nas_message_t *message, pkbuf_t *pkbuf)
{
    nas_attach_complete_t *attach_complete = &message->emm.attach_complete;
    c_uint16_t decoded = 0;
    c_int32_t size = 0;

    size = nas_decode_esm_message_container(
            &attach_complete->esm_message_container, pkbuf);
    d_assert(size >= 0, return -1, "decode failed");
    decoded += size;

    return decoded;
}

c_int32_t nas_decode_authentication_failure(nas_message_t *message, 
        pkbuf_t *pkbuf)
{
    nas_authentication_failure_t *authentication_failure = 
        &message->emm.authentication_failure;
    c_uint16_t decoded = 0;
    c_int32_t size = 0;

    size = nas_decode_emm_cause(&authentication_failure->emm_cause, pkbuf);
    d_assert(size >= 0, return -1, "decode failed");
    decoded += size;

    while(pkbuf->len > 0) 
    {
        c_uint8_t *buffer = pkbuf->payload;
        c_uint8_t type = (*buffer) >= 0x80 ? ((*buffer) & 0xf0) : (*buffer);

        size = sizeof(c_uint8_t);
        d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, return -1, 
                "pkbuf_header error");
        decoded += size;

        switch(type)
        {
            case NAS_AUTHENTICATION_FAILURE_AUTHENTICATION_FAILURE_PARAMETER_TYPE:
                size = nas_decode_authentication_failure_parameter(
                        &authentication_failure->
                        authentication_failure_parameter, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                authentication_failure->presencemask |=
                    NAS_AUTHENTICATION_FAILURE_AUTHENTICATION_FAILURE_PARAMETER_PRESENT;
                decoded += size;
                break;
            default:
                d_error("Unknown type(0x%x) or not implemented\n", type);
                return -1;
        }

    }

    return decoded;
}

c_int32_t nas_decode_authentication_response(nas_message_t *message, 
        pkbuf_t *pkbuf)
{
    nas_authentication_response_t *authentication_response = 
        &message->emm.authentication_response;
    c_uint16_t decoded = 0;
    c_int32_t size = 0;

    size = nas_decode_authentication_response_parameter(
            &authentication_response->authentication_response_parameter, pkbuf);
    d_assert(size >= 0, return -1, "decode failed");
    decoded += size;

    return decoded;
}

c_int32_t nas_decode_security_mode_complete(nas_message_t *message, 
        pkbuf_t *pkbuf)
{
    nas_security_mode_complete_t *security_mode_complete = 
        &message->emm.security_mode_complete;
    c_uint16_t decoded = 0;
    c_int32_t size = 0;

    while(pkbuf->len > 0) 
    {
        c_uint8_t *buffer = pkbuf->payload;
        c_uint8_t type = (*buffer) >= 0x80 ? ((*buffer) & 0xf0) : (*buffer);

        size = sizeof(c_uint8_t);
        d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, return -1, 
                "pkbuf_header error");
        decoded += size;

        switch(type)
        {
            case NAS_SECURITY_MODE_COMPLETE_IMEISV_TYPE:
                size = nas_decode_mobile_identity(
                        &security_mode_complete->imeisv, pkbuf);
                d_assert(size >= 0, return -1, "decode failed");
                security_mode_complete->presencemask |=
                    NAS_SECURITY_MODE_COMPLETE_IMEISV_PRESENT;
                decoded += size;
                break;
            default:
                d_error("Unknown type(0x%x) or not implemented\n", type);
                return -1;
        }

    }

    return decoded;
}

c_int32_t nas_decode_security_mode_reject(nas_message_t *message, 
        pkbuf_t *pkbuf)
{
    nas_security_mode_reject_t *security_mode_reject = 
        &message->emm.security_mode_reject;
    c_uint16_t decoded = 0;
    c_int32_t size = 0;

    size = nas_decode_emm_cause(&security_mode_reject->emm_cause, pkbuf);
    d_assert(size >= 0, return -1, "decode failed");
    decoded += size;

    return decoded;
}

status_t nas_plain_decode(nas_message_t *message, pkbuf_t *pkbuf)
{
    status_t rv = CORE_ERROR;
    c_uint16_t size = 0;
    c_uint16_t decoded = 0;

    d_assert(pkbuf, return CORE_ERROR, "Null param");
    d_assert(pkbuf->payload, return CORE_ERROR, "Null param");

    memset(message, 0, sizeof(nas_message_t));

    size = sizeof(nas_header_t);
    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(&message->h, pkbuf->payload - size, size);
    decoded += size;

    switch(message->h.message_type)
    {
        case NAS_ATTACH_REQUEST:
            size = nas_decode_attach_request(message, pkbuf);
            d_assert(size >= CORE_OK, return CORE_ERROR, "decode error");
            decoded += size;
            break;
        case NAS_ATTACH_ACCEPT:
            break;
        case NAS_ATTACH_COMPLETE:
            size = nas_decode_attach_complete(message, pkbuf);
            d_assert(size >= CORE_OK, return CORE_ERROR, "decode error");
            decoded += size;
            break;
        case NAS_ATTACH_REJECT:
            break;
        case NAS_DETACH_REQUEST:
        case NAS_DETACH_ACCEPT:
        case NAS_TRACKING_AREA_UPDATE_REQUEST:
        case NAS_TRACKING_AREA_UPDATE_ACCEPT:
        case NAS_TRACKING_AREA_UPDATE_COMPLETE:
        case NAS_TRACKING_AREA_UPDATE_REJECT:
        case NAS_EXTENDED_SERVICE_REQUEST:
        case NAS_SERVICE_REJECT:
        case NAS_GUTI_REALLOCATION_COMMAND:
        case NAS_GUTI_REALLOCATION_COMPLETE:
            d_error("Not implemented(0x%x)", message->h.message_type);
            return CORE_ERROR;
        case NAS_AUTHENTICATION_REQUEST:
            break;
        case NAS_AUTHENTICATION_RESPONSE:
            size = nas_decode_authentication_response(message, pkbuf);
            d_assert(size >= CORE_OK, return CORE_ERROR, "decode error");
            decoded += size;
            break;
        case NAS_AUTHENTICATION_REJECT:
            break;
        case NAS_AUTHENTICATION_FAILURE:
            size = nas_decode_authentication_failure(message, pkbuf);
            d_assert(size >= CORE_OK, return CORE_ERROR, "decode error");
            decoded += size;
            break;
        case NAS_IDENTITY_REQUEST:
        case NAS_IDENTITY_RESPONSE:
        case NAS_SECURITY_MODE_COMMAND:
            d_error("Not implemented(0x%x)", message->h.message_type);
            return CORE_ERROR;
        case NAS_SECURITY_MODE_COMPLETE:
            size = nas_decode_security_mode_complete(message, pkbuf);
            d_assert(size >= CORE_OK, return CORE_ERROR, "decode error");
            decoded += size;
            break;
        case NAS_SECURITY_MODE_REJECT:
            size = nas_decode_security_mode_reject(message, pkbuf);
            d_assert(size >= CORE_OK, return CORE_ERROR, "decode error");
            decoded += size;
            break;
        case NAS_EMM_STATUS:
        case NAS_EMM_INFORMATION:
        case NAS_DOWNLINK_NAS_TRANSPORT:
        case NAS_UPLINK_NAS_TRANSPORT:
        case NAS_CS_SERVICE_NOTIFICATION:
        case NAS_DOWNLINK_GENERIC_NAS_TRANSPORT:
        case NAS_UPLINK_GENERIC_NAS_TRANSPORT:

        case NAS_ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST:
        case NAS_ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_ACCEPT:
        case NAS_ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REJECT:
        case NAS_ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_REQUEST:
        case NAS_ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_ACCEPT:
        case NAS_ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_REJECT:
        case NAS_MODIFY_EPS_BEARER_CONTEXT_REQUEST:
        case NAS_MODIFY_EPS_BEARER_CONTEXT_ACCEPT:
        case NAS_MODIFY_EPS_BEARER_CONTEXT_REJECT:
        case NAS_DEACTIVATE_EPS_BEARER_CONTEXT_REQUEST:
        case NAS_DEACTIVATE_EPS_BEARER_CONTEXT_ACCEPT:
        case NAS_PDN_CONNECTIVITY_REQUEST:
        case NAS_PDN_CONNECTIVITY_REJECT:
        case NAS_PDN_DISCONNECT_REQUEST:
        case NAS_PDN_DISCONNECT_REJECT:
        case NAS_BEARER_RESOURCE_ALLOCATION_REQUEST:
        case NAS_BEARER_RESOURCE_ALLOCATION_REJECT:
        case NAS_BEARER_RESOURCE_MODIFICATION_REQUEST:
        case NAS_BEARER_RESOURCE_MODIFICATION_REJECT:
        case NAS_ESM_INFORMATION_REQUEST:
        case NAS_ESM_INFORMATION_RESPONSE:
        case NAS_ESM_STATUS:
        default:
            d_error("Unknown message type (0x%x) or not implemented", 
                    message->h.message_type);
            break;
    }

    rv = pkbuf_header(pkbuf, decoded);
    d_assert(rv == CORE_OK, return CORE_ERROR, "pkbuf_header error");

    return CORE_OK;
}

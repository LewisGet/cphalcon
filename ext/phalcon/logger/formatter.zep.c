
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/hash.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/fcall.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Logger\Formatter
 *
 * This is a base class for logger formatters
 */
ZEPHIR_INIT_CLASS(Phalcon_Logger_Formatter) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Logger, Formatter, phalcon, logger_formatter, phalcon_logger_formatter_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	return SUCCESS;

}

/**
 * Returns the string meaning of a logger constant
 *
 * @param  integer type
 * @return string
 */
PHP_METHOD(Phalcon_Logger_Formatter, getTypeString) {

	zval *type_param = NULL;
	int type;

	zephir_fetch_params(0, 1, 0, &type_param);

	type = zephir_get_intval(type_param);


	do {
		if (type == 7) {
			RETURN_STRING("DEBUG", 1);
		}
		if (type == 3) {
			RETURN_STRING("ERROR", 1);
		}
		if (type == 4) {
			RETURN_STRING("WARNING", 1);
		}
		if (type == 1) {
			RETURN_STRING("CRITICAL", 1);
		}
		if (type == 8) {
			RETURN_STRING("CUSTOM", 1);
		}
		if (type == 2) {
			RETURN_STRING("ALERT", 1);
		}
		if (type == 5) {
			RETURN_STRING("NOTICE", 1);
		}
		if (type == 6) {
			RETURN_STRING("INFO", 1);
		}
		if (type == 0) {
			RETURN_STRING("EMERGENCY", 1);
		}
		if (type == 9) {
			RETURN_STRING("SPECIAL", 1);
		}
		RETURN_STRING("CUSTOM", 1);
	} while(0);


}

/**
 * Interpolates context values into the message placeholders
 *
 * @see http://www.php-fig.org/psr/psr-3/ Section 1.2 Message
 * @param string $message
 * @param array $context
 */
PHP_METHOD(Phalcon_Logger_Formatter, interpolate) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_7 = NULL;
	HashTable *_3;
	HashPosition _2;
	zend_bool _1;
	zval *context = NULL;
	zval *message_param = NULL, *context_param = NULL, *replace, *key = NULL, *value = NULL, *_0, **_4, *_5 = NULL, *_6 = NULL;
	zval *message = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &message_param, &context_param);

	zephir_get_strval(message, message_param);
	ZEPHIR_SEPARATE_PARAM(message);
	if (!context_param) {
	ZEPHIR_INIT_VAR(context);
	ZVAL_NULL(context);
	} else {
		zephir_get_arrval(context, context_param);
	}


	ZEPHIR_INIT_VAR(_0);
	zephir_gettype(_0, context TSRMLS_CC);
	_1 = ZEPHIR_IS_STRING(_0, "array");
	if (_1) {
		_1 = zephir_fast_count_int(context TSRMLS_CC) > 0;
	}
	if (_1) {
		ZEPHIR_INIT_VAR(replace);
		array_init(replace);
		zephir_is_iterable(context, &_3, &_2, 0, 0, "phalcon/logger/formatter.zep", 93);
		for (
		  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
		  ; zephir_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HMKEY(key, _3, _2);
			ZEPHIR_GET_HVALUE(value, _4);
			ZEPHIR_INIT_LNVAR(_5);
			ZEPHIR_CONCAT_SVS(_5, "{", key, "}");
			zephir_array_update_zval(&replace, _5, &value, PH_COPY | PH_SEPARATE);
		}
		ZEPHIR_CALL_FUNCTION(&_6, "strtr", &_7, message, replace);
		zephir_check_call_status();
		zephir_get_strval(message, _6);
	}
	RETURN_CTOR(message);

}

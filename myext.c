#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_myext.h"
#include <stdio.h>

//fonction entry
zend_function_entry myext_functions[] =
{
    ZEND_FE(read_file, NULL)
    {NULL,NULL,NULL} /* end function_entry */
};

PHP_FUNCTION(read_file)
{
  char *path;
  int path_length;
  long buffer;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl",
                            &path, &path_length, &buffer) == FAILURE)
  {
      RETURN_FALSE;
  }

  FILE *file = fopen(path, "r");

  if (!file)
  {
    zend_error(E_ERROR, "Error to open the file : '%s' ", path);
    RETURN_FALSE;
  }
  else
  {
    //for each line, I put this line in array
    char line[buffer];
    long line_number = 0;
    zval *lines;

    object_init(return_value);

    MAKE_STD_ZVAL(lines);
    array_init(lines);

    while(fgets(line, buffer, file) != NULL)
    {
      add_next_index_string(lines, line, 1);
      ++line_number;
    }

    // finally I create simple object with number of line in file
    // and array of line
    add_property_long(return_value, "number_line", line_number);
    add_property_zval(return_value, "lines", lines);

  }

  fclose(file);

  return;
}


/* {{{ myext_module_entry
 */
zend_module_entry myext_module_entry = {
    STANDARD_MODULE_HEADER,
    "myext",
    myext_functions, /* Function entries definit ci dessus */
    NULL, /* Module init */
    NULL, /* Module shutdown */
    NULL, /* Request init */
    NULL, /* Request shutdown */
    NULL, /* Module information */
    "0.1", /* Replace with version number for your extension */
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYEXT
ZEND_GET_MODULE(myext)
#endif


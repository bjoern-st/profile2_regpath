<?php

/**
 * @file
 * Modifications to administrative forms.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function _profile_regpath_form_profile_type_form_alter(&$form, &$form_state, $form_id) {
  if (user_access('administer profile_regpath')) {
    // Grab existing values.
    global $base_url;
    $profile_type = $form['type']['#default_value'];
    $settings     = profile_regpath_regpath_load($profile_type);
    // Unserialize array of miscellaneous display options.
    if (is_object($settings)) {
      $misc = unserialize($settings->misc);
    }

    // Change description of profile's registration checkbox.
    $form['data']['registration']['#title'] = t('Show on all user account registration forms.');
    $form['data']['registration']['#description'] = t('If selected, fields for this profile type will be added to the core user registration page and the administrative add user page.');

    // Create new form fields.
    $form['regpath'] = array(
      '#type' => 'fieldset',
      '#title' => t('Unique registration path'),
    );
    $form['regpath']['status'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable unique registration path'),
      '#default_value' => is_object($settings) && $settings->status ? $settings->status : 0,
      '#description' => t("If checked, a unique registration page utilizing this profile type's fields will be available at the specified URL."),
    );
    $form['regpath']['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Settings'),
      '#states' => array(
        'invisible' => array(
          'input[name="status"]' => array('checked' => FALSE),
        ),
      ),
    );
    // @todo add unlimited cardinality to the path field OR change to textarea
    // and loop through each line.
    $form['regpath']['settings']['path'] = array(
      '#type' => 'textfield',
      '#title' => t('URL path'),
      '#field_prefix' => variable_get('clean_url') ? $base_url . '/' : $base_url . '?q=',
      '#field_suffix' => '/register',
      '#default_value' => is_object($settings) && $settings->path ? $settings->path : '',
      '#description' => t('Please enter the base URL for this registration path.
        <ul>
          <li>Menu router items for [path], [path]/register, [path]/login, and [path]/password will be generated.</li>
          <li>You may use the "user" base path to attach this profile to the default user registration form.</li>
          <li>Do not include any slashes.</li>
        </ul>'
      ),
      '#size' => 20,
    );

    // Custom titles on the login, register, and forgot password pages.
    $form['regpath']['settings']['custom_titles'] = array(
      '#type' => 'checkbox',
      '#title' => t('Set custom page titles for the login, register, and forgot password pages.'),
      '#default_value' => is_object($settings) && isset($misc['custom_titles']) ? (int) $misc['custom_titles'] : 0,
      '#description' => t('Enabling this option will permit you to override the default title of "User Account" on the login, register, and forgot password pages.'),
    );
    $form['regpath']['settings']['custom_titles_settings'] = array(
      '#type' => t('fieldset'),
      '#title' => t('Custom page titles'),
      '#states' => array(
        'invisible' => array(
          'input[name="custom_titles"]' => array('checked' => FALSE),
        ),
      ),
    );
    $form['regpath']['settings']['custom_titles_settings']['login_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Login page title'),
      '#default_value' => is_object($settings) && isset($misc['login_title']) ? $misc['login_title'] : 'User Account',
      '#description' => t('Enter the title you want to display in the login page. The default title is <i>User Account</i>.'),
    );
    $form['regpath']['settings']['custom_titles_settings']['register_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Register page title'),
      '#default_value' => is_object($settings) && isset($misc['register_title']) ? $misc['register_title'] : 'User Account',
      '#description' => t('Enter the title you want to display in the registration page. The default title is <i>User Account</i>.'),
    );
    $form['regpath']['settings']['custom_titles_settings']['password_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Password page title'),
      '#default_value' => is_object($settings) && isset($misc['password_title']) ? $misc['password_title'] : 'User Account',
      '#description' => t('Enter the title you want to display in the request new password page. The default title is <i>User Account</i>.'),
    );

    // Add text fields for custom registration confirmation message.
    $form['regpath']['settings']['confirmation_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display a confirmation message after registration.'),
      '#default_value' => is_object($settings) && isset($misc['confirmation_display']) ? (int) $misc['confirmation_display'] : 0,
      '#description' => t('Enabling this option display a custom confirmation message to the user after a successful registration.'),
    );
    $form['regpath']['settings']['confirmation_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Confirmation Message'),
      '#default_value' => is_object($settings) && isset($misc['confirmation_message']) ? $misc['confirmation_message'] : '',
      '#description' => t('Enter the confirmation message that you would like to display.'),
      '#states' => array(
        'invisible' => array(
          'input[name="confirmation_display"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['regpath']['settings']['fieldset_wrap'] = array(
      '#type' => 'checkbox',
      '#title' => 'Wrap profile fields in a fieldset',
      '#description' => t('If checked, all profile fields for this profile type will be wrapped in a fieldset titled @label on the user registration form.', array('@label' => '')),
      '#default_value' => is_object($settings) && isset($misc['fieldset_wrap']) ? (int) $misc['fieldset_wrap'] : 0,
    );

    // Add form fields for assigning roles during registration.
    $roles = user_roles(TRUE);
    unset($roles[BACKDROP_AUTHENTICATED_RID]);

    // Prepare default value for roles checkbox.
    $default_roles = array();
    $roles_settings = is_object($settings) && $settings->roles ? unserialize($settings->roles) : array();
    $enabled_rids = array_keys($roles_settings);
    foreach ($roles as $rid => $role_name) {
      if (in_array($rid, $enabled_rids)) {
        $default_roles[$rid] = $rid;
      }
      else {
        $default_roles[$rid] = 0;
      }
    }

    $form['regpath']['settings']['roles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Assign roles during registration'),
      '#description' => t('Please select any roles that you would like to automatically assign to users registering via this registration path.'),
      '#options' => $roles,
      '#default_value' => $default_roles,
    );

    $form['regpath']['settings']['weight'] = array(
      '#type' => 'select',
      '#title' => t('Weight'),
      '#description' => t("If multiple sets of profile fields are attached to a single registration path, they will be sorted in ascending order by weight. This will affect both the order of profile fields and the title settings."),
      '#options' => backdrop_map_assoc(range(-10, 10, 1)),
      '#default_value' => is_object($settings) && $settings->weight ? (int) $settings->weight : 0,
    );

    // Add new validate and submit handlers.
    $form['#validate'][] = 'profile_regpath_validate_settings';
    $form['#submit'][] = 'profile_regpath_save_settings';
  }
}

/**
 * Validate profile settings form values.
 */
function profile_regpath_validate_settings($form, &$form_state) {
  if ($form_state['values']['status'] == 1) {
    // Validate URL tail via regex. This also tests that path is not null.
    if (profile_regpath_url_validator(trim($form_state['values']['path'])) == FALSE) {
      form_set_error('path', 'Error, you did not enter a valid URL.');
    }
    // Ensure that URL does not contain a '/'.
    // @todo move this to profile_regpath_url_validator.
    if (strpos($form_state['values']['path'], '/')) {
      form_set_error('path', 'Error, you cannot use a "/" in your unique path. You may specify only a single segment of the URL.');
    }
    // Check to see if another module is using the selected path.
    // We must make exceptions for '/user' and other p2rp registered paths.
    if ($form_state['values']['path'] != 'user' && $existing_item = menu_get_item($form_state['values']['path'])) {
      if ($existing_item['page_callback'] != '_profile_regpath_user_login') {
        form_set_error('path', 'Error, that base path is already being used by another module.');
      }
    }
    // Check to see if selected path is being used by an alias.
    if ($existing_alias = backdrop_lookup_path('source', $form_state['values']['path'])) {
      form_set_error('path', t('Error, that base path is already being used as an alias. Please select a different base path or remove the alias.'));
    }
  }
}

/**
 * Verifies the syntax of the given URL.
 *
 * @param string $url
 *   A string containing a URL.
 *
 * @return boolean
 *   TRUE if the URL is in a valid format, and FALSE if it isn't.
 */
function profile_regpath_url_validator($url) {
  $LINK_ICHARS_DOMAIN = (string) html_entity_decode(implode("", array(
        // æ
        "&#x00E6;",
        // Æ
        "&#x00C6;",
        // ø
        "&#x00F8;",
        // Ø
        "&#x00D8;",
        // å
        "&#x00E5;",
        // Å
        "&#x00C5;",
        // ä
        "&#x00E4;",
        // Ä
        "&#x00C4;",
        // ö
        "&#x00F6;",
        // Ö
        "&#x00D6;",
        // ü
        "&#x00FC;",
        // Ü
        "&#x00DC;",
        // Ñ
        "&#x00D1;",
        // ñ
        "&#x00F1;",
      )), ENT_QUOTES, 'UTF-8');

  $LINK_ICHARS = $LINK_ICHARS_DOMAIN . (string) html_entity_decode(implode("", array(
        // ß
        "&#x00DF;",
      )), ENT_QUOTES, 'UTF-8');

  // Pattern specific to internal links.
  $internal_pattern = "/^(?:[a-z0-9" . $LINK_ICHARS . "_\-+\[\]]+)";

  $directories = "(?:\/[a-z0-9" . $LINK_ICHARS . "_\-\.~+%=&,$'!():;*@\[\]]*)*";
  // Yes, four backslashes == a single backslash.
  $query = "(?:\/?\?([?a-z0-9" . $LINK_ICHARS . "+_|\-\.\/\\\\%=&,$'():;*@\[\]{} ]*))";
  $anchor = "(?:#[a-z0-9" . $LINK_ICHARS . "_\-\.~+%=&,$'():;*@\[\]\/\?]*)";

  // The rest of the path for a standard URL.
  $end = $directories . '?' . $query . '?' . $anchor . '?' . '$/i';

  if (preg_match($internal_pattern . $end, $url)) {
    return TRUE;
  }
}

/**
 * Helper function to save profile settings.
 */
function profile_regpath_save_settings($form, &$form_state) {
  $profile_type = $form_state['values']['type'];
  // $profile_id = profile_regpath_get_profile_id($profile_type);

  // Define fields for db_merge.
  $fields = array(
    'path' => $form_state['values']['path'],
    'status' => $form_state['values']['status'],
    'weight' => $form_state['values']['weight'],
  );

  // Add roles if enabled.
  $roles = array();
  foreach ($form_state['values']['roles'] as $role_id => $enable) {
    if ($enable) {
      $roles[$role_id] = $role_id;
    }
  }
  $fields['roles'] = $roles;

  // Create array of miscellaneous display options.
  $fields['misc'] = array(
      'fieldset_wrap' => $form_state['values']['fieldset_wrap'],
      'custom_titles' => $form_state['values']['custom_titles'],
      'login_title' => $form_state['values']['login_title'],
      'register_title' => $form_state['values']['register_title'],
      'password_title' => $form_state['values']['password_title'],
      'confirmation_display' => $form_state['values']['confirmation_display'],
      'confirmation_message' => $form_state['values']['confirmation_message'],
    );

  // Add settings to database.
  $fields['profile_type'] = $profile_type;
  $fields['profile_id'] = $profile_id;
  profile_regpath_regpath_save($fields);

  // Rebuild menu.
  if (menu_rebuild()) {
    backdrop_set_message(t('The menu system has been rebuilt.'));
  }
}

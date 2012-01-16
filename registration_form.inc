<?php

/**
 * @file
 * Builds profile-specific register, login, and password forms.
 */
function _profile2_regpath_user_register($pids = array()) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_register_form');
  return $output;
}

function _profile2_regpath_user_password() {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_pass');
  return $output;
}

function _profile2_regpath_user_login() {
  module_load_include('pages.inc', 'user', 'user');
  $output = user_page();
  return $output;
}
<?php

/**
 * @file
 * GovCMS update helper functions.
 */

 use Drupal\Core\Extension\ExtensionLifecycle;

/**
 * Enables ckeditor5 module if it is not already enabled.
 */
function govcms_update_10000() {
  // Check if the module is already installed.
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor5')) {
    // If the module is not installed, enable it.
    \Drupal::service('module_installer')->install(['ckeditor5']);
  }
}

/**
 * Transfer obsolete admin theme to Claro.
 */
function govcms_update_10001() {
  // Load the available themes.
  $theme_extension_list = \Drupal::service('extension.list.theme');
  $theme_extension_list->reset();
  // Load the system.theme config.
  $config = \Drupal::configFactory()->getEditable('system.theme');
  $admin_theme = $config->get('admin');
  $admin_theme_info = $theme_extension_list->getExtensionInfo($admin_theme);

  if (isset($admin_theme_info[ExtensionLifecycle::LIFECYCLE_IDENTIFIER])) {
    if ($admin_theme_info[ExtensionLifecycle::LIFECYCLE_IDENTIFIER] === ExtensionLifecycle::OBSOLETE) {
      // Check if the Claro theme is installed.
      $claro_theme = \Drupal::service('theme_handler')->themeExists('claro');
      if (!$claro_theme) {
        // Install the Claro theme.
        \Drupal::service('theme_installer')->install(['claro']);
      }
      // Set claro as the default admin theme.
      $config->set('admin', 'claro')->save();
    }
  }
}

/**
 * Update the pathauto.settings configuration if 'safe_tokens' is not set.
 */
function govcms_update_10002() {
  // Check if the pathauto module is enabled.
  if (\Drupal::moduleHandler()->moduleExists('pathauto')) {
    // Load the current pathauto settings configuration.
    $config = \Drupal::configFactory()->getEditable('pathauto.settings');
    // Check if 'safe_tokens' is not set.
    if (!$config->get('safe_tokens')) {
      // Set default safe tokens.
      $safe_tokens = [
        'alias',
        'alias',
        'path',
        'join-path',
        'login-url',
        'url',
        'url-brief',
      ];
      // Set 'safe_tokens'.
      $config->set('safe_tokens', $safe_tokens)->save();
    }
  }
}

/**
 * Uninstall outdated modules from GovCMS Drupal 9.
 */
function govcms_update_10003() {
  // Placeholder.
}
<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Digest email'),
  'description' => t('Show the digest email a user should get, if was sent now.'),
  'required context' => new ctools_context_required(t('User'), array('user')),
  'category' => t('Topic notify'),
);

/**
 * Render callback.
 */
function topic_notify_digest_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  $module = 'topic_notify';
  $account = $context->data;
  $message = topic_notify_get_digest($account);

  $block = new stdClass();
  $block->module = $module;
  $block->title = t('Digest email');

  $wrapper = entity_metadata_wrapper('user', $account);

  if (!$wrapper->field_send_digest->value()) {
    $block->content = t('@name is not subscribed to a digest email.', array('@name' => format_username($account)));
  }
  elseif (!$message) {
    $block->content = t('@name has no pending messages that need to be processed as a digest email.', array('@name' => format_username($account)));
  }
  else {
    $element = $message->buildContent('full', $account->language);
    $block->content['subject'] = $element['subject'];
    $block->content['body'] = $element['text'];
  }

  return $block;
}

/**
 * Form callback.
 */
function topic_notify_digest_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
  return $form;
}



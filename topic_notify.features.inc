<?php
/**
 * @file
 * topic_notify.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function topic_notify_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_flag_default_flags().
 */
function topic_notify_flag_default_flags() {
  $flags = array();
  // Exported flag: "Notify".
  $flags['notify'] = array(
    'content_type' => 'node',
    'title' => 'Notify',
    'global' => '0',
    'types' => array(
      0 => 'topic',
    ),
    'flag_short' => 'Follow topic',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unfollow topic',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'module' => 'topic_notify',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;
}

/**
 * Implements hook_default_message_type().
 */
function topic_notify_default_message_type() {
  $items = array();
  $items['digest_question_wrapper'] = entity_import('message_type', '{
    "name" : "digest_question_wrapper",
    "description" : "Digest question wrapper (3\\/4)",
    "argument_keys" : [ "@question-author", "@question-url", "@question-title" ],
    "category" : "message_type",
    "message_text" : { "es" : [
        {
          "value" : "@question-author asks: \\u003ca href=\\"@question-url\\"\\u003e@question-title\\u003c\\/a\\u003e",
          "format" : "filtered_html",
          "safe_value" : "\\u003cp\\u003e@question-author asks: \\u003ca href=\\"@question-url\\"\\u003e@question-title\\u003c\\/a\\u003e\\u003c\\/p\\u003e\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['digest_topic_wrapper'] = entity_import('message_type', '{
    "name" : "digest_topic_wrapper",
    "description" : "Digest topic wrapper (2\\/4)",
    "argument_keys" : [ "@count", "@topic-name", "!questions", "@topic-url" ],
    "category" : "message_type",
    "message_text" : { "es" : [
        {
          "value" : "\\u003cstrong\\u003e@count sobre @topic-name:\\u003c\\/strong\\u003e\\n\\n!questions\\n\\n\\u003ca href=\\"@topic-url\\"\\u003eView all questions and answers in @topic-name\\u003c\\/a\\u003e",
          "format" : "filtered_html",
          "safe_value" : "\\u003cp\\u003e\\u003cstrong\\u003e@count sobre @topic-name:\\u003c\\/strong\\u003e\\u003c\\/p\\u003e\\n\\u003cp\\u003e!questions\\u003c\\/p\\u003e\\n\\u003cp\\u003e\\u003ca href=\\"@topic-url\\"\\u003eView all questions and answers in @topic-name\\u003c\\/a\\u003e\\u003c\\/p\\u003e\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['email_topic_digest'] = entity_import('message_type', '{
    "name" : "email_topic_digest",
    "description" : "Email topic digest (1\\/3)",
    "argument_keys" : [ "@subject-topic-list", "@name", "!topic-digest", "!unsubscribe-links" ],
    "category" : "message_type_email",
    "message_text" : { "es" : [
        {
          "value" : "Hello @name,\\r\\nHere is the recent activity in your Medico.com communities. Will you show support for your fellow members by answering some of these questions?\\r\\n\\r\\n!topic-digest\\r\\n\\r\\nEl equipo de Medico.com\\r\\nwww.medico.com\\r\\n\\u003chr \\/\\u003e\\r\\nPara contactar con Medico.com: www.medico.com\\/es\\/contact\\/\\r\\n\\r\\n\\u003cstrong\\u003eHow can I stop receiving messages like this?\\u003c\\/strong\\u003e\\r\\n!unsubscribe-links\\r\\n\\r\\n",
          "format" : "filtered_html",
          "safe_value" : "\\u003cp\\u003eHello @name,\\u003cbr \\/\\u003e\\nHere is the recent activity in your Medico.com communities. Will you show support for your fellow members by answering some of these questions?\\u003c\\/p\\u003e\\n\\u003cp\\u003e!topic-digest\\u003c\\/p\\u003e\\n\\u003cp\\u003eEl equipo de Medico.com\\u003cbr \\/\\u003e\\u003ca href=\\"http:\\/\\/www.medico.com\\"\\u003ewww.medico.com\\u003c\\/a\\u003e\\u003c\\/p\\u003e\\n\\u003cp\\u003ePara contactar con Medico.com: \\u003ca href=\\"http:\\/\\/www.medico.com\\/es\\/contact\\/\\"\\u003ewww.medico.com\\/es\\/contact\\/\\u003c\\/a\\u003e\\u003c\\/p\\u003e\\n\\u003cp\\u003e\\u003cstrong\\u003eHow can I stop receiving messages like this?\\u003c\\/strong\\u003e\\u003cbr \\/\\u003e\\n!unsubscribe-links\\u003c\\/p\\u003e\\n"
        }
      ]
    },
    "message_text_subject" : { "es" : [
        {
          "value" : "@subject-topic-list at Medico.com ",
          "format" : "plain_text",
          "safe_value" : "@subject-topic-list at Medico.com "
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_node_info().
 */
function topic_notify_node_info() {
  $items = array(
    'question' => array(
      'name' => t('Question'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'topic' => array(
      'name' => t('Topic'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

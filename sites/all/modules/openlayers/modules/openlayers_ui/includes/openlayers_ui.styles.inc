<?php

/**
 * @file
 * This file holds the functions handling styles in the
 * Openlayers UI.
 *
 * @ingroup openlayers
 */

/**
 * Styles add/edit form.
 * Defaults and descriptions are taken from OpenLayers.
 * @see http://docs.openlayers.org/library/feature_styling.html
 */
function openlayers_ui_styles_form($form, &$form_state, $style = NULL, $edit = FALSE) {
  $form = array();

  $properties = array(
    'externalGraphic' => array(
      'default' => '',
      'desc' => t('The URL of an icon for points in a layer.  The following options are available:
        <ul><li>Full path, such as http://example.com/icon.png</li>
        <li>Relative Drupal path, such as sites/all/modules/example/icon.png</li>
        <li>Absolute path, such as /icon.png (though this is not suggested for maintainability reasons)</li></ul>'),
    ),
    'pointRadius' => array(
      'default' => 6,
      'desc' => t('The radius of a vector point or the size of
        an icon. Note that, when using icons, this value should be half the
        width of the icon image.'),
      'type' => 'integer',
      'element_validate' => array('element_validate_integer')
    ),
    'fillColor' => array(
      'default' => '#EE9900',
      'desc' => t('This is the color used for
        filling in Polygons. It is also used in the center of marks for
        points: the interior color of circles or other shapes. It is
        not used if an externalGraphic is applied to a point.  This should be
        a hexadecimal value like #FFFFFF.'),
    ),
    'strokeColor' => array(
      'default' => '#EE9900',
      'desc' => t('This is color of the line on features. On
        polygons and point marks, it is used as an outline to the feature.
        On lines, this is the representation of the feature.  This should be
        a hexadecimal value like #FFFFFF.'),
    ),
    'strokeWidth' => array(
      'default' => 1,
      'desc' => t('This is width of the line on features. On
        polygons and point marks, it is used as an outline to
        the feature. On lines, this is the representation of the
        feature.  This is a value in pixels.'),
      'type' => 'integer',
      'element_validate' => array('element_validate_integer')
    ),
    'fillOpacity' => array(
      'default' => 1,
      'desc' => t('This is the opacity used for filling in Polygons.
        It is also used in the center of marks for points: the interior
        color of circles or other shapes. It is not used if an
        externalGraphic is applied to a point.  This should be a value
        between 0 and 1.'),
      'type' => 'float',
      'element_validate' => array('_element_validate_between_zero_and_one', 'element_validate_number')
    ),
    'strokeOpacity' => array(
      'default' => 1,
      'desc' => t('This is opacity of the line on features.
        On polygons and point marks, it is used as an outline to the
        feature. On lines, this is the representation of the feature.
        This should be a value between 0 and 1.'),
      'type' => 'float',
      'element_validate' => array('_element_validate_between_zero_and_one', 'element_validate_number')
    ),
    'strokeLinecap' => array(
      'default' => 'round',
      'desc' => t('Options are butt, round, square. This property
        is similar to the SVG stroke-linecap property. It determines
        what the end of lines should look like. See the SVG link for
        image examples.'),
      'options' => array(
        'butt' => t('Butt'),
        'round' => t('Round'),
        'square' => t('Square'),
      ),
    ),
    'strokeDashstyle' => array(
      'default' => 'solid',
      'desc' => t('Options are dot, dash, dashdot, longdash, longdashdot, solid.'),
      'options' => array(
        'dot' => t('Dot'),
        'dash' => t('Dash'),
        'dashdot' => t('Dash-dot'),
        'longdash' => t('Long-dash'),
        'longdashdot' => t('Long-dash-dot'),
        'solid' => t('Solid'),
      ),
    ),
    'cursor' => array(
      'default' => '',
      'desc' => t('Cursor used when mouse is over the feature. Default
        is an empty string, which inherits from parent elements.  See
        <a href="!url">CSS cursor styles</a>.', array(
          '!url' => 'http://www.w3schools.com/css/pr_class_cursor.asp',
        )),
    ),
    'graphicWidth' => array(
      'default' => '',
      'desc' => t('This properties define the width of an externalGraphic.
        This is an alternative to the pointRadius symbolizer property
        to be used when your graphic has different sizes in the X and
        Y direction.  This should be in pixels.'),
      'type' => 'integer',
      'element_validate' => array('element_validate_integer')
    ),
    'graphicHeight' => array(
      'default' => '',
      'desc' => t('This properties define the height of an externalGraphic.
        This is an alternative to the pointRadius symbolizer property
        to be used when your graphic has different sizes in the X and
        Y direction.  This should be in pixels.'),
      'type' => 'integer',
      'element_validate' => array('element_validate_integer')
    ),
    'graphicOpacity' => array(
      'default' => '1',
      'desc' => t('Opacity of an external graphic.  This should be a
        value between 0 and 1. Grahics that are already semitransparent,
        like alpha PNGs, should have this set to 1, or rendering problems in
        Internet Explorer will ensue.'),
      'type' => 'float',
      'element_validate' => array('_element_validate_between_zero_and_one', 'element_validate_number')
    ),
    'graphicXOffset' => array(
      'default' => '',
      'desc' => t('Where the X value of the "center" of an
      externalGraphic should be.  This should be in pixels.'),
      'type' => 'integer',
      'element_validate' => array('element_validate_integer')
    ),
    'graphicYOffset' => array(
      'default' => '',
      'desc' => t('Where the Y value of the "center" of an
      externalGraphic should be.  This should be in pixels.'),
      'type' => 'integer',
      'element_validate' => array('element_validate_integer')
    ),
    'graphicName' => array(
      'default' => '',
      'desc' => t('Name of a type of symbol to be used
        for a point mark.'),
    ),
    'rotation' => array(
      'default' => '',
      'desc' => t('The rotation angle in degrees clockwise for
        a point symbolizer.'),
    ),
    'display' => array(
      'default' => '',
      'desc' => t('Can be set to "none" to hide features
        from rendering.'),
      'options' => array(
        '' => t('On'),
        'none' => t('None (off)'),
      ),
    ),
    'label' => array(
      'default' => '',
      'desc' => t('A label to show for features. '
        . 'Tipically used with ${attribute} syntax.')
    ),
    'labelAlign' => array(
      'default' => 'cm',
      'desc' => t('Label alignment.'),
      'options' => array(
        'cm' => t('Center, middle'),
        'ct' => t('Center, top'),
        'cb' => t('Center, bottom'),
        'lm' => t('Left, middle'),
        'lt' => t('Left, top'),
        'lb' => t('Left, bottom'),
        'rm' => t('Right, middle'),
        'rt' => t('Right, top'),
        'rb' => t('Right, bottom'),
      ),
    ),
    'labelXOffset' => array(
      'default' => '',
      'desc' => t('Label X offset. Positive numbers move label right.'),
      'element_validate' => array('element_validate_number')
    ),
    'labelYOffset' => array(
      'default' => '',
      'desc' => t('Label Y offset. Positive numbers move label up.'),
      'element_validate' => array('element_validate_number')
    ),
    'fontColor' => array(
      'default' => '',
      'desc' => t('Label font color.'),
    ),
    'fontSize' => array(
      'default' => '',
      'desc' => t('Label font size.'),
    ),
    'fontFamily' => array(
      'default' => '',
      'desc' => t('Label font family.'),
    ),
    'fontWeight' => array(
      'default' => '',
      'desc' => t('Label font weight.'),
    ),
  );

  // Pass style data along
  $form['style_data'] = array(
    '#type' => 'value',
    '#value' => $properties,
  );

  // Style object basics
  $form['info'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
    '#title' => t('Style Basics'),
    '#description' => t('The basic settings for the style.'),
  );

  // Provide a preview of the style
  $preview_style = (isset($form_state['values']) && $form_state['values']['preview_style']) ?
    $form_state['values']['preview_style'] : $style;
  if ($preview_style) {
    $form['info']['preview_style_container'] = array(
      '#type' => 'item',
      '#title' => t('Preview'),
      '#markup' => openlayers_ui_style_preview($preview_style, TRUE),
      '#description' => t('If you are using attribute replacement, the style may not show properly.  The crosshairs point out where the feature is centered.'),
    );
  }

  $form['info']['name'] = array(
    '#title' => t('Style Machine Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($style->name) ? $style->name : '',
    '#description' => t('This is the unique name of the style. It must contain only alphanumeric characters and underscores.'),
  );
  $form['info']['title'] = array(
    '#title' => t('Style Title'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($style->title) ? $style->title : '',
    '#description' => t('The title of your style, which will appear in the administration interface.'),
  );
  $form['info']['description'] = array(
    '#title' => t(' Style Description'),
    '#type' => 'textfield',
    '#default_value' => !empty($style->description) ? $style->description : '',
    '#description' => t('The description of your style, which will appear in the administration interface.'),
  );

  // OpenLayers style properties
  $form['data'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('Style Properties'),
    '#description' => t('The specific properties for the style.'),
  );

  foreach ($properties as $key => $prop) {
    $form['data'][$key] = array(
      '#type' => !isset($prop['options']) ? 'textfield' : 'select',
      '#title' => check_plain($key),
      '#description' => filter_xss($prop['desc']),
      '#default_value' => isset($style->data[$key]) ?
        $style->data[$key] : $prop['default'],
      '#element_validate' => isset($prop['element_validate']) ?
        $prop['element_validate'] : array()
    );

    // Add options if needed
    if (isset($prop['options']) && is_array($prop['options'])) {
      $form['data'][$key]['#options'] = $prop['options'];
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Preview'),
  );
  return $form;
}

/**
 * Validation handler for styles.
 */
function openlayers_ui_styles_form_validate($form, &$form_state) {

}


/**
 * Submit handler for styles.
 */
function openlayers_ui_styles_form_submit(&$form, &$form_state) {
  $style_data = $form_state['values']['style_data'];

  // Cast and unset values so JS can handle them better,
  // Unless values are in the form ${attribute}
  foreach ($form_state['values']['data'] as $key => $value) {
    if ($form_state['values']['data'][$key] === '') {
      unset($form_state['values']['data'][$key]);
    }
    elseif (isset($style_data[$key]['type']) &&
      strpos($form_state['values']['data'][$key], '${') !== 0) {
      if ($style_data[$key]['type'] == 'integer') {
        $form_state['values']['data'][$key] =
          (int) $form_state['values']['data'][$key];
      }
      elseif ($style_data[$key]['type'] == 'float') {
        $form_state['values']['data'][$key] =
          (float) $form_state['values']['data'][$key];
      }
    }
  }

  // Create style object
  $style = new stdClass();
  $style->name = $form_state['values']['name'];
  $style->title = $form_state['values']['title'];
  $style->description = $form_state['values']['description'];
  $style->data = $form_state['values']['data'];

  // On preview, process, but don't save, rebuild.
  if ($form_state['clicked_button']['#id'] == 'edit-preview') {
    $form_state['values']['preview_style'] = $style;
    $form_state['rebuild'] = TRUE;
    return;
  }

  // Save
  $success = openlayers_style_save($style);

  // Redirect to edit page
  if ($success) {
    drupal_set_message(t('Style saved.'));
    $form_state['redirect'] = 'admin/structure/openlayers/styles/' . $style->name . '/edit';
  }
  else {
    form_set_error('openlayers', t('Error trying to save style.'));
  }
}

/**
 * Custom validation function.
 * See #element_validate in Form API.
 */
function _element_validate_between_zero_and_one($element, &$form_state, $form) {
  if ($element['#value'] < 0 || $element['#value'] > 1) {
    form_error($element, t('The @property property must be between 0 and 1.', array('@property' => $element['#title'])));
  }
}
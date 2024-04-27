const id = "PT_EVENT_BACKGROUND_DIALOGUE";
const groups = ["EVENT_GROUP_DIALOGUE"];
const name = "Display Background Dialogue";

const wrap8Bit = (val) => (256 + (val % 256)) % 256;

const decOct = (dec) => wrap8Bit(dec).toString(8).padStart(3, "0");

const fields = [
  {
    key: `nameX`,
    label: "Name X",
    type: "number",
    min: 0,
    max: 19,
    width: "50%",
    defaultValue: 1,
  },
  {
    key: `nameY`,
    label: "Name Y",
    type: "number",
    min: 0,
    max: 17,
    width: "50%",
    defaultValue: 1,
  },
  {
    key: "name",
    label: "Name",
    type: "textarea",
    placeholder: "",
    multiple: false,
    defaultValue: "",
    flexBasis: "100%",
  },
  {
    key: `x`,
    label: "Dialogue X",
    type: "number",
    min: 0,
    max: 19,
    width: "50%",
    defaultValue: 1,
  },
  {
    key: `y`,
    label: "Dialogue Y",
    type: "number",
    min: 0,
    max: 17,
    width: "50%",
    defaultValue: 1,
  },
  {
    key: "text",
    label: "Dialogue",
    type: "textarea",
    placeholder: "",
    multiple: true,
    defaultValue: "",
    flexBasis: "100%",
  },
  {
    key: "spacing",
    label: "Line spacing",
    description: "Whether to add an 8px gap between lines.",
    width: "50%",
    alignCheckbox: true,
    type: "checkbox",
    defaultValue: false,
  },
  {
    key: "arrow",
    label: "Prompt",
    description: "Whether to render a prompt to press a button after text is drawn. Uses the final tile of the current font.",
    width: "50%",
    alignCheckbox: true,
    type: "checkbox",
    defaultValue: false,
  },
];

const compile = (input, helpers) => {
  const {
    appendRaw,
    _addComment,
    _loadStructuredText,
    _displayText,
    _overlayWait
  } = helpers;

  const x = decOct(1 + input.x);
  const y = decOct(1 + input.y);
  const nameX = decOct(1 + input.nameX);
  const nameY = decOct(1 + input.nameY);

  _addComment("Background Dialogue");

  if (helpers.settings.customColorsEnabled) {
    appendRaw(`VM_PUSH_CONST 0
  VM_GET_UINT8 .ARG0, _overlay_priority
  VM_SET_CONST_UINT8 _overlay_priority, 0
  VM_POP 1`);
  }

  appendRaw(`VM_SWITCH_TEXT_LAYER .TEXT_LAYER_BKG`);

  if (!Array.isArray(input.text)) {
    input.text = [input.text];
  }

  for (const boxtext of input.text) {
    _loadStructuredText(`${input.name === "" ? "" : `\\003\\${nameX}\\${nameY}${input.name}`}\\003\\${x}\\${y}${input.spacing ? boxtext.replace(/\n/g, "\n\n") : boxtext}\\003\\023\\021${input.arrow ? "\\005\\377" : ""}`);

    _displayText();

    _overlayWait(false, [".UI_WAIT_TEXT"]);

    _overlayWait(false, [".UI_WAIT_BTN_A"]);

    appendRaw(`VM_CALL_NATIVE b_scroll_repaint, _scroll_repaint`);
  }

  appendRaw(`VM_SWITCH_TEXT_LAYER .TEXT_LAYER_WIN`);

  if (helpers.settings.customColorsEnabled) {
    appendRaw(`VM_PUSH_CONST 0
VM_SET_UINT8 _overlay_priority, .ARG0
VM_POP 1`);
  }
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
  waitUntilAfterInitFade: true,
};

const id = "PT_EVENT_REPAINT_BACKGROUND";
const groups = ["EVENT_GROUP_SCREEN"];
const name = "Repaint Background";

const fields = [
  {
    label: "Repaints background with original scene background and removes any background text or dialogue.",
  },
];

const compile = (input, helpers) => {
  const {
    appendRaw,
  } = helpers;
  
  appendRaw(`VM_CALL_NATIVE b_scroll_repaint, _scroll_repaint`);
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
  waitUntilAfterInitFade: true,
};

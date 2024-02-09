const id = "EVENT_LOAD_SPRITE_SHEET";
const groups = ["EVENT_GROUP_ACTOR"];
const name = "Load Sprite Sheet";

const fields = [
    {
		key: "spriteSheetId",
        type: "sprite",
        label: "Sprite Sheet",
        defaultValue: "LAST_SPRITE",
    },
];

const compile = (input, helpers) => {
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};

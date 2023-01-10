module.exports = {
    extends: ["eslint:recommended", "plugin:prettier/recommended"],
    rules: {
        "@typescript-eslint/no-empty-function": "warn",
        "prettier/prettier": "warn",

        "no-unused-vars": "off",
        "@typescript-eslint/no-unused-vars": [
            "warn",
            { argsIgnorePattern: "^_" },
        ],
    },
};

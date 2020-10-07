---

Checks: '-*,readability-*'

WarningsAsErrors: '*'

CheckOptions:
  - key: readability-function-size.LineThreshold
    value: '40'
  - key: readability-function-size.ParameterThreshold
    value: '5'
  - key: readability-identifier-naming.ClassCase
    value: 'CamelCase'
  - key: readability-identifier-naming.ConstantCase
    value: 'lower_case'
  - key: readability-identifier-naming.EnumCase
    value: 'CamelCase'
  - key: readability-identifier-naming.EnumConstantCase
    value: 'CamelCase'
  - key: readability-identifier-naming.FunctionCase
    value: 'CamelCase'
  - key: readability-identifier-naming.MemberCase
    value: 'lower_case'
  - key: readability-identifier-naming.MethodCase
    value: 'CamelCase'
  - key: readability-identifier-naming.NamespaceCase
    value: 'CamelCase'
  - key: readability-identifier-naming.ParameterCase
    value: 'lower_case'
  - key: readability-identifier-naming.PrivateMemberSuffix
    value: '_'
  - key: readability-identifier-naming.ProtectedMemberSuffix
    value: '_'
  - key: readability-identifier-naming.PublicMemberSuffix
    value: '_'
  - key: readability-identifier-naming.StructCase
    value: 'CamelCase'
  - key: readability-identifier-naming.TypeAliasCase
    value: 'CamelCase'
  - key: readability-identifier-naming.TypedefCase
    value: 'CamelCase'
  - key: readability-identifier-naming.TypeTemplateParameterCase
    value: 'CamelCase'
  - key: readability-identifier-naming.UnionCase
    value: 'CamelCase'
  - key: readability-identifier-naming.ValueTemplateParameterCase
    value: 'lower_case'
  - key: readability-identifier-naming.VariableCase
    value: 'lower_case'
  - key: readability-magic-numbers.IgnoredIntegerValues
    value: '1'
  - key: readability-simplify-boolean-expr.ChainedConditionalReturn
    value: '1'
  - key: readability-simplify-boolean-expr.ChainedConditionalAssignment
    value: '1'

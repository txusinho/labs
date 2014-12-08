var $__2,
    $__3,
    $__5,
    $__6;
var Greeter = function Greeter() {
  "use strict";
};
($traceurRuntime.createClass)(Greeter, {sayHi: function() {
    "use strict";
    var name = arguments[0] !== (void 0) ? arguments[0] : 'Anonymous';
    console.log(("Hi " + name + "!"));
  }}, {});
var greeter = new Greeter();
greeter.sayHi();
var $__1 = [0, [2, 3]],
    a = ($__2 = $__1[$traceurRuntime.toProperty(Symbol.iterator)](), ($__3 = $__2.next()).done ? void 0 : $__3.value),
    $__4 = ($__3 = $__2.next()).done ? void 0 : $__3.value,
    b = ($__5 = $__4[$traceurRuntime.toProperty(Symbol.iterator)](), ($__6 = $__5.next()).done ? void 0 : $__6.value),
    c = ($__6 = $__5.next()).done ? void 0 : $__6.value;
console.log(a, b, c);

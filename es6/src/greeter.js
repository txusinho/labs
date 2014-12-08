class Greeter {
  sayHi(name = 'Anonymous') {
    console.log(`Hi ${name}!`);
  }
}

var greeter = new Greeter();
greeter.sayHi();

var [ a, [b, c]] = [ 0, [2, 3]];
console.log(a, b, c);

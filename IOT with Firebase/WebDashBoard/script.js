// Initialize Firebase
//The project has been deleted in firebase
//fill in your own config info 
  // Initialize Firebase
  var config = {
    apiKey: "AIzaSyAv-xn9B1ctJyI0V2Jf40K6MHTfIg_WTmQ",
    authDomain: "osproject-c90ac.firebaseapp.com",
    databaseURL: "https://osproject-c90ac.firebaseio.com",
    projectId: "osproject-c90ac",
    storageBucket: "osproject-c90ac.appspot.com",
    messagingSenderId: "74692230955"
  };
  firebase.initializeApp(config);

$(document).ready(function(){
  var database = firebase.database();
  var ledStatus;
  var temp;
  var humidity;

  database.ref().on("value", function(snap){
  temp  = snap.val().Temp;
  console.log(temp);
  document.getElementById("temperature").innerHTML =  temp;
  humidity  = snap.val().Humidity;
  document.getElementById("humidity").innerHTML = humidity;
  console.log(humidity);
    ledStatus = snap.val().ledStatus;
    document.getElementById("status").innerHTML = ledStatus;
    console.log(ledStatus);
    if(ledStatus == 1){
      $(".lightStatus").text("The light is on");
    } else {
      $(".lightStatus").text("The light is off");
    }
  });

  $(".lightButton").click(function(){
    var firebaseRef = firebase.database().ref().child("ledStatus");
    if(ledStatus == 1){
      firebaseRef.set(0);
      ledStatus = 0;
    } else {
      firebaseRef.set(1);
      ledStatus = 1;
    }
  });

  var firebaseRef = firebase.database().ref().child("Temp");
});

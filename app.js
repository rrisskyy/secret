//jshint esversion:6
require('dotenv').config()
const express = require("express");
const bodyParser = require("body-parser");
const ejs = require("ejs");
const mongoose = require("mongoose");
const session = require("express-session");
const passport = require("passport");
const passportLocalMongoose = require("passport-local-mongoose");
const path = require("path");

const app = express();

app.use(express.static("public"));
app.set("view engine", "ejs");
app.use(bodyParser.urlencoded({ extended: true }));

app.use(session({
    secret: "Ini rahasia banget",
    resave: false, 
    saveUninitialized: false
})); 

app.use(passport.initialize());
app.use(passport.session());



mongoose.connect("mongodb://localhost:27017/userDB", {useNewUrlParser: true});
// mongoose.set("useCreateIndex", true);

const userSchema = new mongoose.Schema({
    email: String,
    password: String
});

userSchema.plugin(passportLocalMongoose);

const User = new mongoose.model("User", userSchema);

passport.use(User.createStrategy());

passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());



app.get("/", (req, res) => {
    res.render("home");
});

//cookies
app.get('/secrets', (req, res) => {
    if(req.isAuthenticated()) {
        res.render('secrets');
    } else {
        res.redirect('/login');
    }
})

app.get("/logout", (req, res) => {
    req.logout();
    res.redirect("/");
})

app.route("/register")
    .get((req, res) => {
        res.render("register");
    })
    .post((req, res) => {
        // register {username: <username yg di input>}, <password yg diinput>
        User.register({username: req.body.username}, req.body.password, (err, user) => {
            if(err) {
                // Kalau gagal, log errornya dan redirect ke halaman yg sama
                console.log(err);
                // res.redirect('/register');
            } else {
                // Generates a function that is used in Passport's LocalStrategy
                // Setelah berhasil mendaftar, redirect ke secrets.
                passport.authenticate("local")(req, res, () => {
                    res.redirect('/secrets');
                });
            };
        });
        
    });

       


app.route("/login")    
    .get((req, res) => {
        res.render("login");
    })

    .post((req, res) => {
        const user = new User ({
            username: req.body.username,
            password: req.body.password
        });

        req.login(user, (err) => {
            if (err) { 
                return console.log(err); 
            } else {
                passport.authenticate("local")(req, res, () => {
                    res.redirect("/secrets")
                })
            }
            
        })
    });



app.listen(3000, () => {
    console.log("Menghubungkan ke localhost:3000")
})
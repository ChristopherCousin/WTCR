--
-- PostgreSQL database dump
--

-- Dumped from database version 10.6
-- Dumped by pg_dump version 10.6

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: employees; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.employees (
    name_employees character varying,
    surname_employees character varying,
    ean13_employees character varying,
    isworking_employees boolean DEFAULT false
);


ALTER TABLE public.employees OWNER TO usuario;

--
-- Name: logs; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.logs (
    ean13_logs character varying,
    checkindate_logs timestamp without time zone,
    checkoutdate_logs timestamp without time zone
);


ALTER TABLE public.logs OWNER TO usuario;

--
-- Data for Name: employees; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.employees (name_employees, surname_employees, ean13_employees, isworking_employees) FROM stdin;
admin	admin	1234567890123	f
\.


--
-- Data for Name: logs; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.logs (ean13_logs, checkindate_logs, checkoutdate_logs) FROM stdin;
asd	2019-02-27 00:00:00	\N
asd	2019-02-27 00:00:00	\N
asd	2019-02-27 00:00:00	\N
asd	2019-02-27 14:03:38.616922	\N
\.


--
-- PostgreSQL database dump complete
--


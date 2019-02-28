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
    ean13_employees character varying(255),
    name_employees character varying(255),
    surname_employees character varying(255),
    dni_employees character varying(255) NOT NULL,
    isworking_employees boolean
);


ALTER TABLE public.employees OWNER TO usuario;

--
-- Name: logs; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.logs (
    ean13_logs character varying,
    date_logs date,
    hour_logs time without time zone,
    action_logs character varying
);


ALTER TABLE public.logs OWNER TO usuario;

--
-- Data for Name: employees; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.employees (ean13_employees, name_employees, surname_employees, dni_employees, isworking_employees) FROM stdin;
1234567890123	root	root	X1921490R	t
\.


--
-- Data for Name: logs; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.logs (ean13_logs, date_logs, hour_logs, action_logs) FROM stdin;
\.


--
-- Name: employees employees_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employees
    ADD CONSTRAINT employees_pkey PRIMARY KEY (dni_employees);


--
-- PostgreSQL database dump complete
--


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


--
-- Name: addlog(bigint, bigint); Type: FUNCTION; Schema: public; Owner: usuario
--

CREATE FUNCTION public.addlog(serial bigint, actionid bigint) RETURNS void
    LANGUAGE plpgsql
    AS $_$

DECLARE
 cserialid bigint;

BEGIN
  SELECT id into cserialid from serialstorage t WHERE ( t.serial = $1 );
 IF cserialid != 0 THEN
  INSERT INTO history(serialid,date,hour,actionid) values (cserialid,current_timestamp,current_timestamp,$2);
 END IF;
END;
$_$;


ALTER FUNCTION public.addlog(serial bigint, actionid bigint) OWNER TO usuario;

--
-- Name: getemployeestatus(bigint); Type: FUNCTION; Schema: public; Owner: usuario
--

CREATE FUNCTION public.getemployeestatus(serialnumber bigint) RETURNS TABLE(name character varying, isworking boolean)
    LANGUAGE plpgsql
    AS $_$


begin
  RETURN query
select t.name, t.isworking
    from employee t
   INNER JOIN serialstorage ON serialstorage.ID = t.serialid
WHERE serialstorage.serial = $1;



end;
$_$;


ALTER FUNCTION public.getemployeestatus(serialnumber bigint) OWNER TO usuario;

--
-- Name: setisworkingstate(bigint, boolean); Type: FUNCTION; Schema: public; Owner: usuario
--

CREATE FUNCTION public.setisworkingstate(serial bigint, isworking boolean) RETURNS void
    LANGUAGE plpgsql
    AS $_$

DECLARE
 cserialid bigint;

BEGIN
  SELECT id into cserialid from serialstorage t WHERE ( t.serial = $1 );
 IF cserialid != 0 THEN
  UPDATE employee SET isworking = $2 WHERE employee.serialid = cserialid;
 END IF;
END;
$_$;


ALTER FUNCTION public.setisworkingstate(serial bigint, isworking boolean) OWNER TO usuario;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: actions; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.actions (
    id integer NOT NULL,
    name character varying(255)
);


ALTER TABLE public.actions OWNER TO usuario;

--
-- Name: actions_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.actions_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.actions_id_seq OWNER TO usuario;

--
-- Name: actions_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.actions_id_seq OWNED BY public.actions.id;


--
-- Name: employee; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.employee (
    id integer NOT NULL,
    name character varying(15) NOT NULL,
    surname1 character varying(15),
    surname2 character varying(15),
    birthdate date,
    identitytype integer,
    identitynum character varying(255),
    serialtypeid integer,
    serialid integer,
    isworking boolean DEFAULT false
);


ALTER TABLE public.employee OWNER TO usuario;

--
-- Name: employee_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.employee_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.employee_id_seq OWNER TO usuario;

--
-- Name: employee_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.employee_id_seq OWNED BY public.employee.id;


--
-- Name: history; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.history (
    id integer NOT NULL,
    serialid integer,
    date date,
    actionid integer,
    hour time without time zone
);


ALTER TABLE public.history OWNER TO usuario;

--
-- Name: history_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.history_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.history_id_seq OWNER TO usuario;

--
-- Name: history_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.history_id_seq OWNED BY public.history.id;


--
-- Name: identitytype; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.identitytype (
    id integer NOT NULL,
    name character varying(255)
);


ALTER TABLE public.identitytype OWNER TO usuario;

--
-- Name: identitytype_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.identitytype_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.identitytype_id_seq OWNER TO usuario;

--
-- Name: identitytype_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.identitytype_id_seq OWNED BY public.identitytype.id;


--
-- Name: serialstorage; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.serialstorage (
    id integer NOT NULL,
    typeid integer NOT NULL,
    serial bigint NOT NULL,
    active boolean DEFAULT false,
    expired boolean DEFAULT true
);


ALTER TABLE public.serialstorage OWNER TO usuario;

--
-- Name: serialstorage_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.serialstorage_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.serialstorage_id_seq OWNER TO usuario;

--
-- Name: serialstorage_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.serialstorage_id_seq OWNED BY public.serialstorage.id;


--
-- Name: serialtype; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.serialtype (
    id integer NOT NULL,
    name character varying(50)
);


ALTER TABLE public.serialtype OWNER TO usuario;

--
-- Name: serialtype_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.serialtype_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.serialtype_id_seq OWNER TO usuario;

--
-- Name: serialtype_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.serialtype_id_seq OWNED BY public.serialtype.id;


--
-- Name: users; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.users (
    id integer NOT NULL,
    username character varying NOT NULL,
    password character varying,
    privilege integer
);


ALTER TABLE public.users OWNER TO usuario;

--
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.users_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.users_id_seq OWNER TO usuario;

--
-- Name: users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.users_id_seq OWNED BY public.users.id;


--
-- Name: actions id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.actions ALTER COLUMN id SET DEFAULT nextval('public.actions_id_seq'::regclass);


--
-- Name: employee id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee ALTER COLUMN id SET DEFAULT nextval('public.employee_id_seq'::regclass);


--
-- Name: history id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.history ALTER COLUMN id SET DEFAULT nextval('public.history_id_seq'::regclass);


--
-- Name: identitytype id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.identitytype ALTER COLUMN id SET DEFAULT nextval('public.identitytype_id_seq'::regclass);


--
-- Name: serialstorage id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.serialstorage ALTER COLUMN id SET DEFAULT nextval('public.serialstorage_id_seq'::regclass);


--
-- Name: serialtype id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.serialtype ALTER COLUMN id SET DEFAULT nextval('public.serialtype_id_seq'::regclass);


--
-- Name: users id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public.users_id_seq'::regclass);


--
-- Data for Name: actions; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.actions (id, name) FROM stdin;
1	Start Working
2	End of Work
3	Break Time
4	End of Break Time
\.


--
-- Data for Name: employee; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.employee (id, name, surname1, surname2, birthdate, identitytype, identitynum, serialtypeid, serialid, isworking) FROM stdin;
1	Pepito	Perez	Mola	2000-01-01	1	12312231P	1	1	f
3	manuel	perez		2000-01-01	1	1	1	2	t
\.


--
-- Data for Name: history; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.history (id, serialid, date, actionid, hour) FROM stdin;
39	1	2019-03-11	2	00:41:54.890888
40	1	2019-03-11	1	20:29:43.203898
41	1	2019-03-11	2	20:31:16.753579
42	1	2019-03-11	1	21:00:16.992565
43	1	2019-03-11	1	21:00:40.628781
44	1	2019-03-11	1	21:03:54.231453
45	1	2019-03-11	1	21:07:46.229203
46	1	2019-03-11	1	21:08:21.204941
47	1	2019-03-11	1	21:11:02.167535
48	1	2019-03-11	2	21:13:40.429167
49	1	2019-03-11	1	21:15:24.87318
50	1	2019-03-11	2	21:17:03.747
51	1	2019-03-11	2	21:17:23.629564
52	1	2019-03-11	2	21:17:25.815735
53	1	2019-03-11	2	21:17:26.691361
54	1	2019-03-11	2	21:17:35.199955
55	1	2019-03-11	3	21:17:36.13516
56	1	2019-03-11	2	21:17:37.129053
57	1	2019-03-11	3	21:17:38.497086
58	1	2019-03-11	1	21:20:28.60881
59	1	2019-03-11	2	21:21:51.431691
60	1	2019-03-11	2	21:22:06.380644
61	1	2019-03-11	3	21:22:08.394741
62	1	2019-03-11	1	21:29:58.059571
63	1	2019-03-11	1	21:30:56.523267
64	1	2019-03-11	1	21:32:09.544567
65	1	2019-03-11	2	21:32:18.463408
66	1	2019-03-11	2	21:32:33.651561
67	1	2019-03-11	2	21:32:44.853431
68	1	2019-03-11	1	21:33:19.98649
69	1	2019-03-11	2	21:33:29.938582
70	1	2019-03-11	1	22:05:56.214232
71	1	2019-03-11	1	22:06:39.917339
72	1	2019-03-11	1	22:08:29.523623
73	1	2019-03-11	2	22:08:39.226529
74	1	2019-03-11	2	22:10:07.358438
75	1	2019-03-11	1	22:10:14.679054
76	1	2019-03-11	3	22:10:24.295573
77	1	2019-03-11	4	22:10:32.360742
78	1	2019-03-11	2	22:12:32.202794
79	1	2019-03-11	1	22:12:40.185898
80	2	2019-03-11	1	22:12:49.970685
81	1	2019-03-11	3	22:13:03.381008
82	1	2019-03-11	2	22:13:08.207604
83	1	2019-03-11	1	22:13:11.141028
84	2	2019-03-11	4	22:13:38.109708
85	2	2019-03-11	2	22:14:12.422409
86	1	2019-03-11	2	22:14:25.187112
87	1	2019-03-11	1	22:14:34.341239
88	1	2019-03-11	3	22:14:58.2706
89	1	2019-03-11	2	22:15:05.744775
90	1	2019-03-11	1	22:15:15.786927
91	2	2019-03-11	1	22:15:16.331639
92	1	2019-03-11	4	22:15:30.012995
93	1	2019-03-11	2	22:15:30.474896
94	1	2019-03-11	1	22:16:04.930244
95	1	2019-03-11	2	22:16:12.936322
96	1	2019-03-11	1	22:16:25.638806
97	1	2019-03-11	2	22:16:30.500061
98	2	2019-03-11	2	22:16:51.430934
99	2	2019-03-11	1	22:16:58.471251
100	1	2019-03-11	1	22:16:59.784843
101	2	2019-03-11	2	22:17:08.798679
102	1	2019-03-11	3	22:17:13.365844
103	2	2019-03-11	1	22:17:16.724703
104	1	2019-03-11	2	22:17:21.741418
105	2	2019-03-11	3	22:17:24.268333
106	1	2019-03-11	1	22:17:29.132498
107	2	2019-03-11	4	22:17:32.216258
108	1	2019-03-11	2	22:17:36.244735
109	2	2019-03-11	2	22:17:41.119763
110	1	2019-03-11	1	22:43:36.720263
111	2	2019-03-11	1	23:03:26.294214
112	1	2019-03-11	2	23:03:53.028253
113	1	2019-03-11	2	23:03:53.796781
114	1	2019-03-11	1	23:04:10.054322
115	1	2019-03-11	2	23:04:22.44884
116	2	2019-03-11	2	23:04:33.884757
117	1	2019-03-11	1	23:04:52.877366
118	2	2019-03-11	1	23:04:53.363601
119	1	2019-03-11	3	23:05:07.692043
120	1	2019-03-11	3	23:05:08.828505
121	1	2019-03-11	2	23:05:14.899536
122	2	2019-03-11	4	23:05:19.176031
123	2	2019-03-11	2	23:05:28.105543
124	1	2019-03-11	1	23:05:31.595724
125	2	2019-03-11	1	23:05:34.939721
126	2	2019-03-11	2	23:05:46.259805
127	2	2019-03-11	2	23:05:48.503348
128	1	2019-03-11	2	23:06:00.10527
129	1	2019-03-11	2	23:06:04.659212
130	1	2019-03-11	1	23:06:08.102006
131	2	2019-03-11	1	23:06:14.667511
132	1	2019-03-11	2	23:06:19.29108
133	2	2019-03-11	2	23:06:24.978994
134	1	2019-03-11	1	23:06:37.900042
135	2	2019-03-11	1	23:06:46.174919
136	1	2019-03-11	2	23:08:56.662892
137	1	2019-03-12	1	00:28:19.990345
138	1	2019-03-12	2	00:29:23.747746
139	2	2019-03-12	2	19:32:11.527064
140	2	2019-03-12	1	19:32:17.534736
141	2	2019-03-12	3	19:32:24.639896
142	2	2019-03-12	2	19:33:48.020109
143	2	2019-03-12	1	19:33:53.693143
\.


--
-- Data for Name: identitytype; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.identitytype (id, name) FROM stdin;
1	DNI
\.


--
-- Data for Name: serialstorage; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.serialstorage (id, typeid, serial, active, expired) FROM stdin;
1	1	9780471117094	f	f
2	1	4006381333931	f	f
\.


--
-- Data for Name: serialtype; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.serialtype (id, name) FROM stdin;
1	ean13
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.users (id, username, password, privilege) FROM stdin;
1	root	root	3
\.


--
-- Name: actions_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.actions_id_seq', 4, true);


--
-- Name: employee_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.employee_id_seq', 3, true);


--
-- Name: history_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.history_id_seq', 143, true);


--
-- Name: identitytype_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.identitytype_id_seq', 1, true);


--
-- Name: serialstorage_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.serialstorage_id_seq', 2, true);


--
-- Name: serialtype_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.serialtype_id_seq', 1, true);


--
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.users_id_seq', 1, true);


--
-- Name: actions PKaction; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.actions
    ADD CONSTRAINT "PKaction" PRIMARY KEY (id);


--
-- Name: employee PKemployee; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "PKemployee" PRIMARY KEY (id);


--
-- Name: history PKhistory; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.history
    ADD CONSTRAINT "PKhistory" PRIMARY KEY (id);


--
-- Name: identitytype PKidentityType; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.identitytype
    ADD CONSTRAINT "PKidentityType" PRIMARY KEY (id);


--
-- Name: serialstorage PKserialStorage; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.serialstorage
    ADD CONSTRAINT "PKserialStorage" PRIMARY KEY (id);


--
-- Name: serialtype PKserialType; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.serialtype
    ADD CONSTRAINT "PKserialType" PRIMARY KEY (id);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id, username);


--
-- Name: employee FKIdentityType; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "FKIdentityType" FOREIGN KEY (identitytype) REFERENCES public.identitytype(id);


--
-- Name: employee FKSerial; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "FKSerial" FOREIGN KEY (serialid) REFERENCES public.serialstorage(id);


--
-- Name: employee FKSerialType; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "FKSerialType" FOREIGN KEY (serialtypeid) REFERENCES public.serialtype(id);


--
-- PostgreSQL database dump complete
--

